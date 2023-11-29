#include <iostream>
#include <string.h>
#include <map>
#include <vector>
#include <fstream>

using namespace std;

class Global;
class ATM;
class Session;
class Card;
class Transaction;
class Bank;
class Account;

// 1. Card Class
// -------------------------------[Card] class-----------------------------------
// -------------------------------[Card] class-----------------------------------

///황지영

class Card {
    //admin 여부, bank, account 정보

private:
    string cardNumber;
    string accountNumber;
    bool isAdmin;
    //bool isBilingual; // 양 언어 구성이 카드와 관련이 있다고 가정

public:
    Card ( ) {
    }
    // 생성자
    Card(const string& cardNumber, const string& accountNumber, bool isAdmin)
        : cardNumber(cardNumber), accountNumber(accountNumber), isAdmin(isAdmin) {}

    // 카드 번호를 가져오는 함수
    const string& getCardNumber() const {
        return cardNumber;
    }

    // 계정 번호를 가져오는 함수
    const string& getAccountNumber() const {
        return accountNumber;
    }

    // 카드가 관리자 카드인지 확인
    //[유리] card number와 password를 받아서 Admin인지 확인해주세요
    bool isAdminCard() const {
        return isAdmin;
    }
/*
    // 카드가 양 언어 지원으로 구성되어 있는지 확인
    bool isBilingualCard() const {
        return isBilingual;
    }
*/
    // 카드 유효성 검사, 인증과 관련된 다른 함수들도 추가할 수 있음
};


//2. Account Class
// -------------------------------[Account] class-----------------------------------
// -------------------------------[Account] class-----------------------------------

//account 를 여는, 만드는 constroctor 필요. 입력 받으면 그걸

class Account {

private:
    string accountNum;
    string password;
    string ownerName;
    Card associatedCard;
    int balance;
    Bank* myBank; // Bank 클래스의 전방 선언 사용 ,  포인터 연결은 여기서 해주는게 맞음

public:
    // 생성자: AccountNum, Password, OwnerName 설정
    Account(const string& accountNum, const string& password, const string& ownerName, Bank* bank)
        : accountNum(accountNum), password(password), ownerName(ownerName), myBank(bank), balance(0) {}

    // Password 검증 함수
    bool verifyPW(const string& enteredPassword) const {
        return (password == enteredPassword);
    }

    // AccountNum 반환 함수
    const string& getAccountNum() const {
        return accountNum;
    }

    // OwnerName 반환 함수
    const string& getOwnerName() const {
        return ownerName;
    }

    // Bank 반환 함수
    Bank* getBank() const {
        return myBank;
    }

    // 잔액 조회 함수
    int getBalance() const {
        return balance;
    }

    // 입금 함수
    void deposit(int amount) {
        balance += amount;
    }

    // 출금 함수
    void withdraw(int amount) {
        if (amount <= balance) {
            balance -= amount;
        }
        else {
            cout << "잔액이 부족합니다." << std::endl;
        }
    }
};


//3. ATM Class
// -------------------------------[ATM] class-----------------------------------
// -------------------------------[ATM] class-----------------------------------
class ATM {
private:
    const int SerialNumber;
    map<string, Bank*> PrimaryBank;
    map<string, Bank*> NonPrimaryBank;
    map<int, int> AvailableCash;//현금 단위, 갯수
    ////////////////////////////////////////change 11.28
    int AvailableCashAmount;//현금 양
    Card* AdminCard;
    map<string, string> History;
    bool Bilingual = false;
    bool MultiBank = false;
    static int NumberOfATM;
    Session* CurrentSession;
    ////////////////////////////////////////change 11.28
    Global* myGlobal;

public:
    ATM();
    ATM(Bank* pb, map<string, Bank*> allb, Card* admin);//primary bank pointer, allbankmap, admincard
    ~ATM();
    void Start();
    bool CheckAdmin();
    bool CheckInvalidCard();
    void OpenSession();

    //Set 함수
    void SetAvailableCash(map<int, int>, bool);
    ////////////////////////////////////////change 11.28
    void SetGlobal(Global* inglobal){this->myGlobal = inglobal;};

    //Get 함수
    int GetSerialNum() { return this->SerialNumber; }
    map<string, Bank*> GetPrimaryBank() { return this->PrimaryBank; }
    map<string, Bank*> GetNonPrimaryBank() { return this->NonPrimaryBank; }
    map<int, int> GetAvailableCash() { return this->AvailableCash; }
    Card* GetAdminCard() { return this->AdminCard; }
    map<string, string> GetHistory() { return this->History; }
    int GetAvailableCashAmount(){return this->AvailableCashAmount;}
    

    //Is 함수
    bool IsMultiBank() { return this->MultiBank; }
    bool IsMBilingual() { return this->Bilingual; }


    //Show 함수
    void ShowHistory();
    void ShowAvailableCash();
};



//4. Session Class
// -------------------------------[Session] class-----------------------------------
// -------------------------------[Session] class-----------------------------------
class Session {
private:
    ATM * atm ; // ATM 객체 가리키는 포인터
    Account* account ; // 계좌 객체 가리키는 포인터
    Card* card ;
    vector<Transaction> transctionHistoryOfSession ; // 세션 동안 거래 내역 저장 -> 하고 뭐햇는지 display 해야함. 하나 저장 후 보여주기 (이걸 함수로먼들지 그냥 코드를 짤지는선택 ) + 백터 구조가 어떤지 알려줘서 ATM에 할수 있게 하기
    bool authorizationSignal ; // 계좌 비밀번호 인증 결과 나타내는 bool값
    int aouthorizationCount ; // 비밀번호 인증 실패 횟수
    int withdrawalCount ; // 출금 횟수 기록
    bool primarySignal ;  // 현재 계좌 은행 정보와 ATM 주거래 은행이 동일한지 여부를 나타내는 bool 값
    int currentTransactionID;
    ////////////////////////////////////////change 11.28
    Global* myGlobal;
    

public:

    Session() : currentTransactionID(1) {}
    void CashDeposit(map<int, int>, int x);
    //void Session::CashDeposit(map<int, int> amount, int x)
    void CheckDeposit(unsigned long long amount, int x);
    //void Withdrawal(unsigned long long amount, int x);
    void Withdrawal(const map<int, int>& amount, int x);
    void CashTransfer(map<int, int>, Account* destination, int x);
    void AccountTransfer(unsigned long long amount, Account* destination, int x);
    bool Authorization(string password) {return account->verifyPW(password);}
    
    int GetNextTransactionID() {
        return currentTransactionID++;
    }
    void SetmyGlobal(Global* inglobal){this->myGlobal = inglobal;};
    

    
};



// -------------------------------[Transaction] class-----------------------------------
// -------------------------------[Transaction] class-----------------------------------
class Transaction {
private:
    ATM* CurrentATM;
    Account* CurrentAccount;
public:

    //void CheckInput();//cash인지 check인지 확인해 CheckCash 또는 CheckCheck 호출
    void CheckCash() {
        map<int, int> CashInATM = CurrentATM->GetAvailableCash();
    };//cash 종류별 개수, bank, username, accountnum, password
    void CheckCheck() {
        int CheckInAccount = CurrentAccount->getBalance();
    };//amount, username, accountnum, password
};


//----------------child of Transaction----------------------
class DepositTransaction : public Transaction {
    //아직 미구현: There is a limit in the number of cash or checks that can be deposited per transaction (e.g., 50 papercashes, 30 paper checks)
public:
    string Deposit(ATM* CurrentATM, Account* CurrentAccount, bool isCash, map<int,int> depositCash) {
        //수수료 책정
        int fee;
        Bank* tmp;
        for (const auto& pair : CurrentATM->GetPrimaryBank()) { tmp = pair.second; }
        if (CurrentAccount->getBank() == tmp) {//error : ==연산자 사용 불가
             fee = 0;
        }
        else { fee = 1000; }
        
        //예치금 액수 계산
        int depositCash_sum = 0;
        for (const auto& entry : depositCash) {
            depositCash_sum += entry.first * entry.second;
        }
        
        //cash or check
        if (isCash == true) {
            //ATM available cash 증가
            map<int, int> available1 = CurrentATM->GetAvailableCash();
            map<int, int> available2;
            for (const auto& entry : available1) {
                available2[entry.first] = entry.second + depositCash[entry.first];//error : available1.first에서 first member가 없다고 하는데 확인해주세요
            }
            CurrentATM->SetAvailableCash(available2, true);
        }
        
        //account 액수 증가
        CurrentAccount->deposit(depositCash_sum + fee);//error : fee가 정의되어있지 않습니다
        
        //history return
        return "cash deposit KRW " + to_string(depositCash_sum) + "(balance now: KRW " + to_string(CurrentAccount->getBalance()) + ")";//error : to_string이 정의되어있지 않습니다
    };
};

class withdrawTransaction : public Transaction {
public:
    string Withdraw(ATM* CurrentATM, Account* CurrentAccount, int Amount) {
        //bank에서 계좌 확인 후 limit 안넘으면 출금, bank 확인해 fee 결정해 빼고 출금, ATM의 available_cash 감소, 최대 50만원 withdraw 가능
        //수수료 책정
        int fee;
        Bank* tmp;
        for (const auto& pair : CurrentATM->GetPrimaryBank()) { tmp = pair.second; }
        if (CurrentAccount->getBank() == tmp) {
            int fee = 1000;
        }
        else { int fee = 2000; }

        map<int, int> AvailableNow = CurrentATM->GetAvailableCash();

        //ATM available money amount
        int ATMCash_sum = 0;
        for (const auto& entry : AvailableNow) {
            ATMCash_sum += entry.first * entry.second;
        }

        //int out_50000 = 0; int out_10000 = 0; int out_5000 = 0; int out_1000 = 0;
        map<int, int> out;
        int tmp_amount = Amount;
        //인출 가능한가?
        if (ATMCash_sum >= tmp_amount) {
            //금액권 개수 산정
            if (AvailableNow[50000] >= int(tmp_amount / 50000)) {
                out[50000] = int(tmp_amount / 50000);
                tmp_amount -= 50000 * out[50000];
            }
            else {
                int out_50000 = AvailableNow[50000];
            }
            if (AvailableNow[10000] >= int(tmp_amount / 10000)) {
                out[10000] = int(tmp_amount / 10000);
                tmp_amount -= 10000 * out[10000];
            }
            else {
                int out_10000 = AvailableNow[10000];
            }
            if (AvailableNow[5000] >= int(tmp_amount / 5000)) {
                out[5000] = int(tmp_amount / 5000);
                tmp_amount -= 5000 * out[5000];
            }
            else {
                int out_5000 = AvailableNow[5000];
            }
            out[1000] = int(tmp_amount / 1000);
            tmp_amount -= 1000 * out[1000];

            //ATM available cash 감소
            map<int, int> AvailableUpdate;
            for (const auto& pair : AvailableNow) {
                AvailableUpdate[pair.first] = pair.second - out[pair.first];//error : first 멤버가 없습니다
            }
            CurrentATM->SetAvailableCash(AvailableUpdate, false);

            //Account balance 감소
            CurrentAccount->withdraw(Amount + fee);//error : fee가 정의되어있지 않습니다

            //history return
            return "cash withdrawal KRW " + to_string(Amount) + "(balance now: KRW" + to_string(CurrentAccount->getBalance()) + ")";//error : to_string이 정의되어있지 않습니다

        }
        else { //인출 불가능
            return "error: The user ordered withdrawal of an amount that exceeds the amount currently available from the ATM.";
        }
    };
};

class TransferTransaction : public Transaction{
public:
    string AccountTransfer(ATM* CurrentATM, Account* Account1, Account* Account2, int Amount) {
        //transfer 가능한가?
        if (Account1->getBalance() >= Amount) {
            //수수료 책정
            int fee;
            Bank* tmp;
            for (const auto& pair : CurrentATM->GetPrimaryBank()) { tmp = pair.second; }
            if (Account1->getBank() == tmp && Account2->getBank() == tmp) {//error : ==연산자 사용 불가
                int fee = 3000;
            }
            else if (Account1->getBank() == tmp || Account2->getBank() == tmp) {//error : ==연산자 사용 불가
                int fee = 4000;
            }
            else { int fee = 5000; }

            Account1->withdraw(Amount + fee);//error : fee가 정의되어있지 않습니다 //error :
            Account2->deposit(Amount);

            //return history
            return "cash transfer KRW " + to_string(Amount) + ", from " + Account1->getAccountNum() + " to " + Account1->getAccountNum();//error : to_string이 정의되어있지 않습니다
        }
        else { // 잔액부족
            return "error: The user ordered transfer of an amount that exceeds the amount currently available from the account.";
        };
    };

    string CashTransfer(ATM* CurrentATM, Account* Account1, Account* Account2, map<int,int> Cash) {//error : map의 type이 정의되어있지 않습니다(ex. map<int,int> Cash)
        int Cash_sum = 0;
        for (const auto& entry : Cash) {
            Cash_sum += entry.first * entry.second;
        }

        //transfer 가능한가?
        if (Account1->getBalance() >= Cash_sum) {
            if (Cash_sum == 5000) {
                //수수료 책정
                Bank* tmp;
                for (const auto& pair : CurrentATM->GetPrimaryBank()) { tmp = pair.second; }
                if (Account1->getBank() == tmp && Account2->getBank() == tmp) {
                    int fee = 3000;
                }
                else if (Account1->getBank() == tmp || Account2->getBank() == tmp) {
                    int fee = 4000;
                }
                else { int fee = 5000; }
                
                Account1->withdraw(Cash_sum);
                Account2->deposit(Cash_sum);
                
                //return history
                return "cash transfer KRW " + to_string(Cash_sum) + ", from " + Account1->getAccountNum() + " to " + Account1->getAccountNum();//error : CurrentAccount에 액세스할 수 없습니다, to_string이 정의되어 있지 않습니다, Amount가 정의되어있지 않습니다}
                }
            else {
                 return "error: The amount came in ATM is not KRW 5000.";
            }
        }
        else { // 잔액부족
            return "error: The user ordered transfer of an amount that exceeds the amount currently available from the account.";
        }//error : if문이 필요합니다
    };
};



////////////////////////////////////////change 11.28
//5. Global Class
class Global{
private:
    map<string, Account*> AccountMap;
    map<string, ATM*> ATMMap;
    char SecretCode = 'x';
public:
    Global();
    Global(map<string, Account*>, map<string, ATM*>);
    ~Global();
    map<string, Account*> getAccountMap(){return this->AccountMap;}
    map<string, ATM*> getATMMap(){return this->ATMMap;}
    char getSecretCode(){return this->SecretCode;}
    void setAccountMap(map<string, Account*>);
    void setATMMap(map<string, Account*>);
    void Display();
    
};


/*-------------- Methods of Session Class --------------*/

//1. 현금 입금 함수
void Session::CashDeposit(map<int, int> amount, int x) { // 야기서 x 는 한국어 인지 아닌지

    unsigned long long fee = 0;
    if (!primarySignal) fee = 1000;

    // ATM에 화폐를 추가합니다.
    atm->SetAvailableCash(amount,true);  // ATM에 돈을 추가하는거면true, 빼는 거면 false 맞는지 확인 필요.

    // 계좌에 입금합니다.
    unsigned long long totalAmount = 0;
    for (const auto& entry : amount) {
        int denomination = entry.first;
        int count = entry.second;
        totalAmount += (denomination * count);
    }
    int transactionID = GetNextTransactionID();
    account->deposit(totalAmount - fee);

    
    
    // ------[history 관리]
    Transaction CashDepositTransaction(transactionID, card->getCardNumber(), "CashDeposit", totalAmount) ;
    transctionHistoryOfSession.push_back(CashDepositTransaction);
    //------------------
    
    
    
    // 거래 정보를 출력합니다. ~에는 뱅크 이름이랑 어카운트 가져오기 기능을 추가 해야함.
    if (x == 0)
        cout << "~에 " << totalAmount << " 원이 입금되었습니다." << endl;
    else
        cout << "~에 " << totalAmount << " won has been deposited." << endl;

    // 현재 잔액을 출력합니다.
    if (x == 0) cout << "/n현재 잔액 : ";
    else cout << "\nCurrent Available Cash : ";
    cout << account->getBalance();
    
    if (x == 0) cout << " 원" << endl;
    else cout << " won" << endl;

    cout << "\n";
}




// 2. 수표를 입금해주는 함수
void Session::CheckDeposit(unsigned long long amount, int x) {
    unsigned long long fee = 0;
    if (!primarySignal) fee = 1000;
    unsigned long long totalAmount = amount - fee ;
        account->deposit(totalAmount);
    
    
    //질문 , ATM에는 돈을 안넣나요. ? .?
    
    // ------[history 관리]
    int transactionID = GetNextTransactionID();
    Transaction CheckDepositTransaction(transactionID, card->getCardNumber(), "CheckDeposit", totalAmount) ;
    transctionHistoryOfSession.push_back(CheckDepositTransaction);
    //-------------------
    
    // 거래 정보를 출력합니다. ~에는 뱅크 이름이랑 어카운트 가져오도록 수정합니다.
    if (x == 0)
        cout << "~에 " << totalAmount << " 원이 입금되었습니다." << endl;
    else
        cout << "~에 " << totalAmount << " won has been deposited." << endl;

    
    //현재 잔액 출력
    if (x == 0) cout << "\n현재 잔액 : ";
    else cout << "\nCURRENT BALANCE : ";
    cout << account->getBalance();
    
    if (x == 0) cout << " 원" << endl;
    else cout << " won" << endl;
    
    cout << "\n";
}


// 3. 출금해주는 함수
void Session::Withdrawal(const map<int, int>& amount, int x) {
    unsigned long long fee = 1000;
    if (!primarySignal) fee = 2000;

    // ATM의 사용 가능한 현금을 가져옴
    map<int, int> availableCash = atm->GetAvailableCash();

    
    unsigned long long totalAvailableCash = 0;
    for (const auto& entry : availableCash) {
        int denomination = entry.first;
        int count = entry.second;
        totalAvailableCash += (denomination * count);
    }

    unsigned long long totalAmount = 0;
    for (const auto& entry : amount) {
        int denomination = entry.first;
        int count = entry.second;
        totalAmount += (denomination * count);
    }

    if (totalAvailableCash < totalAmount + fee) {
        if (x == 0) cout << " 현재 기기 내 현금이 부족합니다\n" << endl;
        else cout << " OUR ATM DOESN'T HAVE ENOUGH MONEY\n" << endl;
    } else if (totalAmount + fee > account->getBalance()) {
        if (x == 0) cout << "잔액 부족\n" << endl;
        else cout << " YOU DON'T HAVE ENOUGH MONEY\n" << endl;
    } else {
        // 출금금액과 수수료를 ATM과 계좌에서 각각 차감
        atm->SetAvailableCash(amount,false);  // 가능한 돈을 차감하는 함수로 가정
        account->withdraw(totalAmount + fee);

        int transactionID = GetNextTransactionID();
        account->deposit(totalAmount - fee);

        
        // ------[history 관리]
        Transaction withdrawTransaction(transactionID, card->getCardNumber(), "Withdraw", totalAmount);
        transctionHistoryOfSession.push_back(withdrawTransaction);
        //------------------

        // 결과 출력
        // 거래 정보를 출력합니다. ~에는 뱅크 이름이랑 어카운트 가져오기 ?
        if (x == 0)
            cout << "~에 " << totalAmount << " 원이 입금되었습니다." << endl;
        else
            cout << "~에 " << totalAmount << " won has been deposited." << endl;

        withdrawalCount++;  // 세션 종료 !! 변수가 있음 ATM에서 가져가면 될듯 ??
        if (x == 0) cout << "\n현재 잔액 : ";
        else cout << "\nCURRENT BALANCE : ";
        cout << account->getFundInfo();
        if (x == 0) cout << " 원" << endl;
        else cout << " won" << endl;
        cout << "\n";
    }
}



// 4. 현금 송금하는 함수
void Session::CashTransfer(map<int, int> amount, Account* destination, int x) { //destination는 이체하고 자 하는 계좌.

    unsigned long long fee = 5000 ;
    
    // ATM에게 현금을 추가합니다.
    atm->SetAvailableCash(amount, true);
    
    
 // 수수료 빼고 계좌에 입금
    unsigned long long totalAmount;
    for (const auto& entry : amount) {
        int denomination = entry.first;
        int count = entry.second;
        unsigned long long totalAmount = (denomination * count);
    }
    
    unsigned long long totaltotalAmount =  totalAmount - fee;
    destination-> deposit ( totaltotalAmount ) ;
    
    int transactionID = GetNextTransactionID();
    
    // ------[history 관리]
    Transaction CashTransferTransaction(transactionID, card->getCardNumber(), "CashTransfer", totaltotalAmount) ;
    transctionHistoryOfSession.push_back(CashTransferTransaction);
    //------------------

   
    // 이체 거래의 정보를 출력합니다. (x가 0이면 한국어, 1이면 영어 출력)
    if (x == 0)
        cout << newTransaction.getKoreanInformation() << endl;
    else
        cout << newTransaction.getEnglishInformation() << endl;

    // 현재 계좌의 잔액을 출력합니다.
    if (x == 0)
        cout << "\n현재 잔액 : ";
    else
        cout << "\nCURRENT BALANCE : ";
    cout << account->getBalance();

    // 통화 단위를 출력합니다.
    if (x == 0)
        cout << " 원" << endl;
    else
        cout << " won" << endl;

    // 개행 문자를 출력합니다.
    cout << "\n";
}


//5. 계좌 송금하는 함수
//수정이 많이 필요합니다.
//계좌 포인터 건드는 법을 모르겠어요 ㅠ
void Session::AccountTransfer(unsigned long long amount, Account* destination, int x) {
    
    // 이체 수수료(fee)를 초기화합니다.
    unsigned long long fee;

    // 송금 계좌와 수취 계좌의 은행 이름을 가져옵니다.
    string accountNum = (findAccount(account->getAccountNum()))->getBankName();
    
    
    string destNum = (findAccountOfBank(destination->getAccountNumber()))->getBankName();

    // 은행이 같고, 현재 세션이 주거래 은행인 경우 수수료는 2000원,
    // 은행이 같고, 현재 세션이 타은행 거래 가능인 경우 수수료는 3000원,
    // 은행이 다른 경우 수수료는 4000원으로 설정합니다.
    if ((accountNum.compare(destNum) == 0) && (primarySignal == true))
        fee = 2000;
    else if ((accountNum.compare(destNum) == 0) && (primarySignal == false))
        fee = 3000;
    else
        fee = 4000;

    // 잔액이 충분하지 않으면 메시지 출력 후 종료합니다.
    if (amount + fee > account->getBalance()()) {
        if (x == 0)
            cout << "잔액 부족\n" << endl;
        else
            cout << "YOU DON'T HAVE ENOUGH MONEY\n" << endl;
    } else {
        // 송금 계좌에서 송금액과 수수료를 차감합니다.
        account->withdraw(<#int amount#>)(amount + fee);

        // 수취 계좌에 송금액을 추가합니다.
        destination->deposit(<#int amount#>)(amount);

        // ------[history 관리]
        AccountTransferTransaction newTransaction(destination, account, amount, accountNum, destNum);
        destination->addTransaction(&newTransaction);

        transactionHistoryOfSession.push_back(newTransaction);
        //------------------
        

        // 송금 거래의 정보를 출력합니다. (x가 0이면 한국어, 1이면 영어 출력)
        if (x == 0)
            cout << newTransaction.getKoreanInformation() << endl;
        else
            cout << newTransaction.getEnglishInformation() << endl;

        // 현재 송금 계좌의 잔액을 출력합니다.
        if (x == 0)
            cout << "\n현재 잔액 : ";
        else
            cout << "\nCURRENT BALANCE : ";
        cout << account->getFundInfo();

        // 통화 단위를 출력합니다.
        if (x == 0)
            cout << " 원" << endl;
        else
            cout << " won" << endl;

        // 개행 문자를 출력합니다.
        cout << "\n";
    }
}







// History에서 withdraw 3번 넘으면 session 종료

// -------------child of Session class ---------------
class KoreanSession : public Session {
public:
    void mainKoreanDisplay() {
        cout << atm->getPrimaryBank() << " 은행" << endl;
        if (atm->getSingleInfo() == 0) cout << "주거래 은행 전용>" << endl;
        else cout << "타은행 거래 가능>" << endl;
    }
    
    KoreanSession(ATM* iatm) {
        // 세션 파라미터 초기화
        atm = iatm;
        primarySignal = true;
        authorizationCount = 0;
        withdrawalCount = 0; // 이거 처리 !
        authorizationSignal = true;
        
        bool validAccount = true; // 계좌 정보 유무
        string inputAccount;
        mainKoreanDisplay();
        bool input;
        while (input) {
            cout << " 계좌 번호를 입력해주세요\n" << endl;
            cout << "계좌 번호 : ";
            cin >> inputAccount;
            input = false;
            if( sel == 'x' ){
                this->myGlobal->Display();
                input = true;
            }
        }
        //이 부분 어떻게 할지 .. ?
        Bank* temp = this->myBank->findAccountOfBank(inputAccount);
        
        
        if (temp == nullptr) {
            mainKoreanDisplay();
            cout << "입력한 계좌번호가 존재하지 않습니다." << endl;
            validAccount = false;
        }
        else { //계좌가 존재하는 경우
            if ( (atm->GetPrimaryBank()).compare(temp->getBankName()) == 0 ) { //현재 세션에서 사용 중인 ATM 객체(atm)의 기본 은행 정보와, 입력된 계좌 번호에 해당하는 Bank 객체의 은행 이름을 비교 ! 두 은행 이름이 같다면, 현재 세션에서 사용 중인 은행이라는 것을 의미
                account = temp->findAccountOfBank(inputAccount); //같다면, 해당 은행에서 입력된 계좌 번호에 해당하는 Account 객체를 찾아서 account 포인터에 저장합니다. 이렇게 하면 현재 세션에서 사용할 수 있는 계좌를 설정
            } else {
                if (atm->IsMultiBank() == 0 ) { //타은행 계좌를 사용할 수 없다면
                    mainKoreanDisplay();
                    cout << "타은행 계좌는 사용하실 수 없습니다\n" << endl;
                    validAccount = false;
                } else {
                    primarySignal = false;
                    account = temp->findAccountOfBank(inputAccount);
                }
            }
        }
        
        if (validAccount) { // 유효한 계좌인 경우 (비밀번호 인증 로직)
            
            for (int i = 1; i < 4; i++) { // 비밀번호 3번까지 입력 가능 !
                string inputPassword;
                mainKoreanDisplay();

            while (input) {
                cout << "비밀번호를 입력해주세요\n" << endl;
                cout << "비밀번호 : ";
                cin >> inputPassword;
                input = false;
                if( sel == 'x' ){
                    this->myGlobal->Display();
                    input = true;
                }
            }
                if (Authorization(inputPassword)) {
                    authorizationSignal = true;
                    break;
                } else if( sel == 'x' ){
                    this->myGlobal->Display();
                } else {
                    authorizationSignal = false;
                    authorizationCount ++;
                    mainKoreanDisplay();
                    cout << "비밀번호를 " << authorizationCount << "회 틀렸습니다\n" << endl;
                }
            }
            
            if (authorizationSignal == false) {
                mainKoreanDisplay();
                cout << " 비밀번호 입력을 3회 실패하여 세션이 종료됩니다" << endl;
            }
            
            else { //비밀번호 인증 통과 후 로직들
                bool sessionExitSignal = true;
                while (sessionExitSignal) {
                    mainKoreanDisplay();
                    cout << "원하시는 서비스를 선택해주세요\n" << endl;
                    cout << "1. 입금    2. 출금   3. 송금   4. 거래 내역 조회   5. 서비스 종료\n" << endl; //거래 3번 이상 시 세션 새로 열기
                    cout << "번호 입력 : ";
                    int transactionNum = -1;
                    cin >> transactionNum;
                    input = false;
                    if( transactionNum == 0000000000 ){
                        this->myGlobal->Display();
                        continue;
                    }
                    if (cin.fail() == true) { // 사용자의 입력이 숫자가 아닌 경우
                        cout << "유효하지 않은 번호입니다." << endl;
                        cin.clear();
                        cin.ignore(100, '\n');
                        continue; //for문 다시 돌아가서 선택하게 하기.
                    }
                    if (transactionNum == 1) { // 입금 (1000월 , 5000원 , 10000원, 50000원을 받아야함. )
                        mainKoreanDisplay() ;
                        cout << " 입금 서비스 입니다. \n" << endl;
                        cout << " 1. 현금 입금     2. 수표 입금\n" << endl;
                        cout << "번호 입력 : ";
                        int depositinput = -1;
                        cin >> depositinput;
                        
                        if (cin.fail() == true) {
                            cout << "유효하지 않은 번호입니다." << endl; //유효하지 않은 입력값 일때 !
                            cin.clear();
                            cin.ignore(100, '\n');
                            continue;
                        } else if (depositinput == 0000000000) {
                            this->myGlobal->Display();
                            continue;
                        }
                    };
                        
                        
                        
                        
                        
                        
                        
                        if ( depositinput == 1) {
                            while (true) {
                                
                                mainKoreanDisplay() ;
                                map<int, int> billCounts; // 각 지폐의 갯수를 저장할 맵
                                cout << "입금하실 지폐의 종류를 선택해주세요\n" << endl;
                                cout << "1. 1000원  2. 5000원  3. 10000원  4. 50000원 5. 종료" << endl;
                                cout << "번호 입력 : ";
                                int bill = -1;
                                cin >> bill;
                                
                                if (cin.fail() == true || bill < 1 || bill > 4) {
                                    cout << "유효하지 않은 번호입니다." << endl;
                                    cin.clear();
                                    cin.ignore(100, '\n');
                                    continue;
                                } else if (bill == 0000000000) {
                                    this->myGlobal->Display();
                                    continue;
                                }
                                
                                if (bill == 5) {
                                    // 사용자가 종료를 선택했을 때 루프를 종료
                                    break;
                                }
                                
                                int billType = -1;
                                
                                if (bill == 1 ) {
                                    
                                    billType = 1000 ;
                                    
                                } else if ( bill == 2 ){
                                    billType = 5000 ;
                                    
                                } else if (bill== 3){
                                    billType = 10000 ;
                                    
                                } else if (bill == 4) {
                                    billType = 50000 ;
                                    
                                }
                                
                                cout << "입금하실 지폐의 장 수를 입력해주세요: ";
                                int numBill = -1;
                                
                                cin >> numBill;
                                if (cin.fail() == true || numBill <= 0) {
                                    cout << "유효하지 않은 번호입니다." << endl;
                                    cin.clear();
                                    cin.ignore(100, '\n');
                                    continue;
                                } else if (numBill == 0000000000) {
                                    this->myGlobal->Display();
                                    continue;
                                }
                                
                                // 각 지폐 종류와 갯수를 맵에 저장
                                billCounts[billType] = numBill;
                                
                                
                                //-------한번에 거래 가능한 장수
                                
                                if (numBill > 50) {
                                    cout << " 거래 1회 당 입금 가능한 장 수를 초과하셨습니다\n" << endl;
                                    break;
                                    
                                }
                                
                            }
                            
                            CashDeposit(billCounts, 0);
                            
                        } else if (depositinput == 2) {
                            // 수표 입금 처리
                            // 사용자에게 10만원권 수표의 장 수를 입력 받아 입금 처리합니다.
                            
                            cout << "수표를 입력해주세요\n" << endl;
                            cout << "수표 : ";
                            int numBill = -1;
                            cin >> numBill;
                            
                            if (cin.fail() == true) { //잘못입력시
                                cout << "유효하지 않은 번호입니다." << endl;
                                cin.clear();
                                cin.ignore(100, '\n');
                                continue;
                            } else if (bill == 0000000000) {
                                this->myGlobal->Display();
                                continue;
                            }
                            if ((0 < numBill) && (numBill <= 30)) {inAmount = 100000 * numBill; break;}
                            else if (numBill > 30) {
                                atm->mainKoreanDisplay();
                                cout << "       거래 1회 당 입금 가능한 장 수를 초과하셨습니다\n" << endl;
                            } else {
                                cout << "유효하지 않은 번호입니다." << endl;
                            }
                            
                            CheckDeposit(inAmount, 0);
                            
                            
                        } else {
                            cout << "유효하지 않은 번호입니다." << endl;
                        }
                        
                        
                        
                    }
                    
                    eles if (transactionNum == 2) {// 출금
                        //세션이 닫치게 만들어야함 !!!!!!!!!
                        
                        if (withdrawalCount == 3) {
                            cout << "       세션 1회 당 출금 가능한 액수를 초과하셨습니다\n" << endl;
                        }
                        
                        else {
                            while (true){
                                mainKoreanDisplay();
                                map<int, int> billCounts; // 각 지폐의 갯수를 저장할 맵
                                cout << "출금하실 지폐의 종류를 선택해주세요\n" << endl;
                                cout << "1. 1000원  2. 5000원  3. 10000원  4. 50000원  5. 종료" << endl;
                                cout << "번호 입력 : ";
                                int bill = -1;
                                cin >> bill;
                                
                                if (cin.fail() == true || bill < 1 || bill > 5) {
                                    cout << "유효하지 않은 번호입니다." << endl;
                                    cin.clear();
                                    cin.ignore(100, '\n');
                                    continue;
                                } else if (bill == 0000000000) {
                                    this->myGlobal->Display();
                                    continue;
                                }
                                
                                if (bill == 5) {
                                    // 사용자가 종료를 선택했을 때 루프를 종료
                                    break;
                                }
                                
                                if (bill == 1) {
                                    
                                    billType = 1000;
                                    
                                } else if (bill == 2) {
                                    billType = 5000;
                                    
                                } else if (bill == 3) {
                                    billType = 10000;
                                    
                                } else if (bill == 4) {
                                    billType = 50000;
                                    
                                }
                                
                                cout << "입금하실 지폐의 장 수를 입력해주세요: ";
                                int numBill = -1;
                                
                                cin >> numBill;
                                if (cin.fail() == true || numBill <= 0) {
                                    cout << "유효하지 않은 번호입니다." << endl;
                                    cin.clear();
                                    cin.ignore(100, '\n');
                                    continue;
                                    
                                } else if (bill == 0000000000) {
                                    this->myGlobal->Display();
                                    continue;
                                }
                                
                                billCounts[billType] = numBill;
                                // 한 번에 거래 가능한 장 수
                                if (numBill > 50) {
                                    cout << "거래 1회 당 입금 가능한 장 수를 초과하셨습니다." << endl;
                                    break;
                                    
                                }
                            }
                            Withdraw(billCounts, 0) ;
                            
                        }
                        
                        
                    }
                    
                    
                    else if (transactionNum == 3) { // 송금
                        cout << "송금 서비스 입니다\n" << endl;
                        cout << "             1. 계좌 송금 (계좌 -> 계좌)" << endl;
                        cout << "             2. 현금 송금 (현금 -> 계좌)\n" << endl;
                        cout << "==================================================" << endl;
                        cout << "번호 입력 : ";
                        int transferNum = -1;
                        cin >> transferNum;
                        if (cin.fail() == true) {
                            cout << "유효하지 않은 번호입니다." << endl;
                            cin.clear();
                            cin.ignore(100, '\n');
                            continue;
                        } else if (transferNum == 0000000000) {
                            this->myGlobal->Display();
                            continue;
                        }
                        
                        if (transferNum == 1) { // Account Transfer
                            cout << "계좌 송금 서비스를 선택하셨습니다\n" << endl;
                            cout << "송금하실 금액을 입력해주십시오\n" << endl;
                            cout << "송금 금액 : ";
                            unsigned long long inAmount = -1;
                            cin >> inAmount;
                            if (cin.fail() == true) {
                                cout << "유효하지 않은 번호입니다." << endl;
                                cin.clear();
                                cin.ignore(100, '\n');
                                continue;
                            } else if (inAmount == 0000000000) {
                                this->myGlobal->Display();
                                continue;
                            }
                            if (inAmount < 0) { cout << "유효하지 않은 번호입니다." << endl;}
                            else if (inAmount == 0) {
                                cout << "0 원을 송금할 수는 없습니다\n" << endl;
                            } else {
                                mainKoreanDisplay() ;
                                cout << "          받으실 분의 계좌 번호를 입력해주십시오\n" << endl;
                                cout << "받으실 분 계좌 번호 : ";
                                string inDest;
                                cin >> inDest;
                                if (findAccount(inDest) == nullptr) { //Global Class 에 있다고 일단 가정
                                    cout << "입력한 계좌번호가 존재하지 않습니다\n" << endl;
                                } else {
                                    AccountTransfer(inAmount, findAccount(inDest) , 0); << endl;
                                    //매개변수 method of ATM이랑 같이해서 확인해 봐야함.
                                }
                            }
                        }else { // Exception
                            cout << "입력한 계좌번호가 존재하지 않습니다\n" << endl;
                        }
                        
                    }
                    
                    // !!!!!!!!!!!!!!!!!히스토리.....
                    
                    else if (transactionNum == 4) { // 거래 내역 조회// Transaction History
                        
                        cout << "거래 내역 조회를 선택하셨습니다\n" << endl;
                        cout << " 해당 계좌의 거래내역은 다음과 같습니다\n" << endl;
                        vector<Transaction> temp = account->getTransactionHistoryOfAccount();
                        if (temp.size() == 0) {
                            cout << "현재 잔액 : " << account->getFundInfo() << " 원\n" << endl;
                            cout << "            해당 계좌에는 거래 내역이 업습니다\n" << endl;
                        } else {
                            for (int i = 0; i < temp.size(); i++) {
                                cout << temp[i].getKoreanInformation() << endl;
                            }
                            cout << "\n현재 잔액 : " << account->getFundInfo() << " 원\n" << endl;
                        }
                        
                    }
                    
                    if (transactionNum == 5) { // 서비스 종료
                        
                        sessionExitSignal = false;
                    }
                    
                    
                    
                    
                }
                
                cout << "세션 종료" << endl;
                cout << "ATM을 이용해주셔서 감사합니다\n" << endl;
                if (transactionHistoryOfSession.size() == 0) {  //히스토리 부분
                    cout << "해당 세션에는 거래 내역이 없습니다\n" << endl;
                } else {
                    cout << "해당 세션 내 총 거래 내역" << endl;
                    
                    atm->addTransaction(transactionHistoryOfSession); //ATM에 넘겨주기.
                    
                    for (int i = 0; i < transactionHistoryOfSession.size(); i++) {
                        cout << transactionHistoryOfSession[i].getKoreanInformation() << endl; // 내역 출력
                    }
                    
                }
            }
        }

        
    } ; //koreansessionclass 끝


class EnglishSession {
public:

};









//5.Bank class
// -------------------------------[Bank] class-----------------------------------
// -------------------------------[Bank] class-----------------------------------

class Bank {
private:
    map<string, Account*> accounts; // 계좌 번호를 키로 사용
    string bankName;

public:

    Bank(string name) : bankName(name) {}; // Bank name 설정

    // 현재 account 있는지 확인하 없으면 생성
    void createAccount(string accountNum, string password, string ownerName) {
        if (!accountExists(accountNum)) {
            accounts[accountNum] = Account(accountNum, password, ownerName, this);
        }
    }

    // 사용자 정보를 모두 출력하는 함수 (특정 사용자의 모든 계정 정보를 출력하는 함수)
    void allAccount(string username) {
        cout << "사용자 " << username << "의 모든 계정 정보:" << endl;
        for (auto entry : accounts) {
            if (entry.second->getOwnerName() == username) {
                cout << "계좌 번호: " << entry.second->getAccountNum() << ", ";
                cout << "잔액: " << entry.second->getBalance() << endl;
            }
        }
    }

    // 사용자 정보를 확인하는 함수 (사용자 정보를 확인하고, 주어진 사용자 이름, 계좌 번호, 비밀번호와 일치하는지 여부를 반환하는 함수)
    bool verifyUser(string username, string accountNum, string password) {
        auto it = accounts.find(accountNum);
        if (it != accounts.end()) {
            Account* account = it->second;
            return (account->getOwnerName() == username && account->verifyPW(password));
        }
        return false; // 사용자 확인 실패
    }

    // 계정 정보를 확인하는 함수(계정 정보를 확인하고, 주어진 계좌 번호와 비밀번호가 일치하는지 여부를 반환하는 함수)
    bool verifyAccount(string accountNum, string password) {
        auto it = accounts.find(accountNum);
        return (it != accounts.end() && it->second->verifyPW(password));
    }

    // 계좌 존재 여부 확인 (주어진 계좌 번호가 은행에 존재하는지 여부를 확인하는 함수) //Account의 pointer를 반환하면?
    bool accountExists(int accountNum) {
        return { accounts.find(accountNum) != accounts.end() };
    }


    // 은행 이름 리턴 함수
    string getBankName() { return bankName; };

    // Bank 클래스의 소멸자
    ~Bank() {
    // 소멸자에서 리소스 정리 작업 수행
    // 예: 동적으로 할당된 메모리 해제 등

    map<string, Account*> AccountsInBank() { return accounts }
};









///--------------------------------method of ATM-------------------------------------

ATM::ATM() {
    cout << "아무 input 없이 ATM을 생성할 수 없습니다." << endl;
    cout << "primary bank의 pointer, 모든 bank의 map, admin card의 pointer를 넣어 ATM을 생성해주세요." << endl;
    cout << "자동으로 이 ATM을 제거합니다." << endl;
    delete this;

}

ATM::ATM(Bank* pb, map<string, Bank*> allb, Card* admin) {
    //primary bank pointer, allbankmap, admincard

    //변수 선언
    string bankname;
    Bank* bankpointer;
    int mul;
    int bi;
    int cash1000;
    int cash5000;
    int cash10000;
    int cash50000;

    //UI
    cout << "ATM을 생성합니다" << endl;
    cout << "Serial Number" << endl;
    cin >> this->SerialNumber;
    cout << "Primary Bank name :" << endl;
    cin >> bankname;
    this->PrimaryBank.insert({ bankname, pb });
    allb.erase("bankname");
    this->NonPrimaryBank.insert(allb);
    cout << "Primary 및 Nonprimary bank 설정이 완료되었습니다" << endl;
    this->AdminCard = admin;
    cout << "Admin Card 설정이 완료되었습니다" << endl;
    while (true) {
        cout << "Bilingual ATM입니까?" << endl;
        cout << "숫자로 입력해주세요" << endl;
        cout << "[1]Yes    [2]No" << endl;
        cin >> bi;

        if (bi == 1) {
            this->Bilingual = true;
            break;
        }
        else if (bi == 2) {
            this->Bilingual = false;
            break;
        }
        else {
            cout << "올바르지 않은 숫자입니다. 다시 입력해주세요" << endl;
        };
    };

    while (true) {
        cout << "MultiBank ATM입니까?" << endl;
        cout << "숫자로 입력해주세요" << endl;
        cout << "[1]Yes    [2]No" << endl;
        cin >> mul;

        if (mul == 1) {
            this->MultiBank = true;
            break;
        }
        else if (mul == 2) {
            this->MultiBank = false;
            break;
        }
        else {
            cout << "올바르지 않은 숫자입니다. 다시 입력해주세요" << endl;

        };
    };
    cout << "초기 Cash를 입금해주세요" << endl;
    cout << "1000원권 몇 장을 입금하시겠습니까?" << endl;
    cin >> cash1000;
    this->AvailableCash.insert({ 1000,cash1000 });
    cout << "5000원권 몇 장을 입금하시겠습니까?" << endl;
    cin >> cash5000;
    this->AvailableCash.insert({ 5000,cash5000 });
    cout << "10000원권 몇 장을 입금하시겠습니까?" << endl;
    cin >> cash10000;
    this->AvailableCash.insert({ 10000,cash10000 });
    cout << "50000원권 몇 장을 입금하시겠습니까?" << endl;
    cin >> cash50000;
    this->AvailableCash.insert({ 50000,cash50000 });
    ++NumberOfATM;
}

ATM::~ATM() {
    delete this->CurrentSession;
    NumberOfATM--;
}
void Start() {
//기본적인 모든 session 열기 전 수행을 하는 함수입니다.
    
    //기본 선택 : (Card 입력받기)
    int firstsel;
    cout << "Welcome" << endl;
    cout << "To start a session, please insert your debit card" << endl;
    int CN, PW;
        cout << "Insert card number and password" << endl;
        //Card 입력받은 경우 : admin인지, 올바른 카드인지 확인 후 session 열어주기
        if (CheckAdmin(CN, PW)) {
            int sel = 1;
        bool repeat = true;
            cout << "Welcome Administrator" << endl;
        while (repeat){
                cout << "[1] Transaction History" << endl;
                cin >> sel;
                
                if (sel == 1) {
                        ShowHistory();
                repeat = false;
                } else if (transferNum == 0000000000) {
                        this->myGlobal->Display();
                        continue;
                } else {
                        cout << "error : 올바른 input을 입력해주세요" << endl;
                }
        }
        }
        else {
        if (CheckInvalidCard(CN, PW)){
            OpenSession();
        }else{ cout << "올바르지 않은 카드입니다." << endl;}
           
        };
    //Session 종료 또는 invalid card : 카드 return 표시하기
        
};
bool (int cardnum, string pw){
     ///////////////////////////////이 부분 어떻게 할지, bank에서 카드 맵 저장하는게 나을지도
    bool isExist = false;
    for (const auto& pair : PrimaryBank) {
        map<string, Account*> accs = PrimaryBank.second->AccountsinBank();
        for (const auto& pair : accs) {
            if(accs.second->getAccountNum() == cardnum && accs.second->verifyPW(pw)) {
                isExist = true;
            }
        }
    }
    for (const auto& pair : NonPrimaryBank) {
        map<string, Account*> accs = NonPrimaryBank.second->AccountsinBank();
        for (const auto& pair : accs) {
            if(accs.second->getAccountNum() == cardnum && accs.second->verifyPW(pw)) {
                isExist = true;
            }
        }
    }
    return isExist;
};

bool CheckAdmin(int cardnum, int pw) {
    return this->AdminCard->isAdminCard(cardnum, pw);
};
bool OpenSession() {
    //언어 받고 session열어주기
    if (this->Bilingual) {
        int sel;
        cout << "Select Language" << endl;
        cout << "[1] English [etc] Korean" << endl;
        if (sel == 1) {
            this->CurrentSession = new EnglishSession();
            CurrentSession.SetmyGlobal(this->myGlobal);
        }
        else {
            this->CurrentSession = new KoreanSession();
            CurrentSession.SetmyGlobal(this->myGlobal);
        }
    }
};
void SetAvailableCash(map<int, int> inputcash, bool Plus) {
    if (Plus) {
        for (auto iter = this->AvailableCash.begin(); iter != this->AvailableCash.end(); iter++) {
            int currentnum = inputcash.find(iter->first)->second;
            iter->second += currentnum;
    } else {
        for (auto iter = this->AvailableCash.begin(); iter != this->AvailableCash.end(); iter++) {
            int currentnum = inputcash.find(iter->first)->second;
            iter->second -= currentnum;
    };
    int sum;
    for(auto iter = this->AvailableCash.begin(); iter != this->AvailableCash.end(); iter++){
        sum+=((iter->first)*(iter->second));
    };
    this->AvailableCashAmount = sum;
};
void ShowHistory() {
    //Transaction History 보여주기 - user명과 transaction id, card num, transaction type, amount 등 정보
    //map[<"TransactionID",int>,<"CardNumber",int>,<"TransactionType",string>,<"Amount",int>]
    std::ofstream out("History.txt", std::ios::app);
    if (out.is_open()) {
        cout << "----------------------History--------------------" << endl;
        out << "----------------------History--------------------" << endl;
        for (auto iter = this->History.begin(); iter != this->History.end(); iter++) {
            cout << iter->first << " : " << iter->second << endl;
            out << iter->first << " : " << iter->second << endl;
        };
        cout << "------------------------------------------------" << endl;
        out << "------------------------------------------------" << endl;
    }
    else {
        cout << "Error : history 파일 안열림" << endl;
    };


};
void ShowAvailableCash() {
    int total = 0;
    cout << " Remaining Cash: ( ";
        for (auto iter = this->AvailableCash.begin(); iter != this->AvailableCash.end(); iter++) {
            cout << iter->first << "원X" << iter->second << "장  ";
            total += iter->first * iter->second;
        };
    cout << ") total : " << total << endl;
};
////////////////////////////////////////change 11.28
//----------------------------methods of Global----------------------------------------
//-------------------------------------------------------------------------------------
void Global::setAccountMap(map<string,Account*> inmap){
    this->AccountMap = inmap;
};
void Global::setATMMap(map<string,ATM*> inmap){
    this->ATMMap = inmap;
};
void Global::Display(){
    //모든 ATM의 정보 출력
    for (pair<string, ATM*> i : ATMMap){
        cout << "(ATM [SN : "<<i.second->GetSerialNum();
        cout << "] remaining cash: "<<i.second->AvailableCashAmount()<<" ) ";
    };

    //모든 Account의 정보 출력
    for (pair<string, Account*> p: AccountMap){
        cout << "(Account [Bank: "<<p.second->myBank->getBankName()<<", No: " <<p.first;
        cout << ", Owner: "<<p.second->getOwnerName()<<"] balance: "<<p.second->getBalance()<<" ) ";
    };
};




int main() {

    //Bank 선언
    int NumofBank;
    string InputBankName1;
    map <string, Bank*> InputBankMap;
    cout << "BANK를 선언하겠습니다" << endl;
    cout << "몇개의 은행을 만드시겠습니까? << endl;
    cin >> NumofBank;
    for (int i=0; i<NumofBank; i++){
        cout << "은행의 이름을 입력해주세요" << endl;
        cin >> BankName1;
        InputBankMap.insert({BankName1,new Bank(BankName1)});
    };

    //Account 선언
    map<int, Account*> AccountMap;
    int NumofAccount;
    string pb;
    int AccountNum;
    string pw;
    string ownername;
    cout << "Account를 선언하겠습니다" << endl;
    cout << "몇개의 Account를 만드시겠습니까? << endl;
    cin >> NumofAccount;
    for (int i=0; i<NumofAccount; i++){
        cout << "계좌의 주거래 은행을 알려주세요" << endl;
        cin >> pb;
        cout << "계좌번호를 입력해주세요" << endl;
        cin >> AccountNum;
        cout << "계좌 소유주의 성명을 입력해주세요" << endl;
        cin >> ownername;
        cout << "계좌 비밀번호를 입력해주세요" << endl;
        cin >> pw;
        Account(AccountNum, pw, ownername, InputBankMap[pb]()); //수정중
        AccountMap.insert({AccountNum, new Account(AccountNum, pw, ownername, InputBankMap[pb]())});

        //Card 선언
        //적어도 admin card는 여기에서 선언되어 ATM을 생성할 때 넣어줘야 함.
        cout << "카드를 만드시겠습니까? (y, n)" << endl;
        cin >> char makeCard;
        if (makeCard == "y") {
            cout << "카드번호를 입력하세요" << endl;
            int cardNumber;
            cin >> cardNumber;
            cout << "관리자 권한을 부여하시겠습니까? (y, n)" << endl;
            char askAdmin;
            cin >> askAdmin;
            bool isAdmin;
            if (askAdmin = "y") { isAdmin = true; }
            else { isAdmin = false; }
            
            Card(cardNumber, NumofAccount, isAdmin);
        }
    }
    

    //ATM선언 전 primary bank pointer, bankmap, card pointer가 준비되어 있어야 함
    //ATM 선언
    map<string, ATM*> ATMmap;
    int ATMNum;
    string ATMname;
    string AdminCard;
    string InputPrimaryBank;
    cout << "ATM을 설정하겠습니다" << endl;
    cout << "몇개의 ATM을 만드시겠습니까?" << endl;
    cin >> ATMNum;
    for (int i=0; i<ATMNum; i++){
        //Primary Bank Setting
        cout << "아래 중 ATM의 주거래 은행을 선택하세요" << endl;
        cout << "[";
        for (int iter=InputBankMap.begin(); iter != InputBankMap.end() ; iter++){
            cout << iter->first << ",";
        };
        cout << "]" << endl;
        cin >> InputPrimaryBank;
        cout << "ATM의 이름을 설정하세요." << endl;
        cin >> ATMname;
        cout << "Admin Card를 정하세요." << endl;
        cin >> AdminCard;
        ATMmap.insert({ATMname, new ATM(InputBankMap.find(InputPrimaryBank), InputBankMap, AdminCard)});
    }
    ////////////////////////////////////////change 11.28
    Global myGlobal(AccountMap, ATMMap);
    for (auto& i : ATMMap){
        i.second->SetGlobal();
    };
        
    ////////////////////////////////////////question 11.28
    bool isATMworiking = true;
    while (isATMworking) {
        //display
        for (const auto& pair : AccountMap) {
                cout << "[Account " << pair.first << "] Remaining Cash: KRW " << pair.second->getBalance() << endl;
            }
        for (const auto& pair : ATMmap) {
                cout << "[ATM " << pair.first << "];
            pair.second->showAvailableCash();
            }
    
        //select ATM
        string UsedATM;
        cout << "Write the name of an ATM that you want to use." << endl;
        cin << UsedATM;
        if (UsedATM == 'x') {
            myGlobal->Display();
            continue;
        }
        
        ATMmap[UsedATM]->Start();

        //quit?
        char isQuit;
        cout << "Do you want to terminate current program? (y, n)" << endl;
        cin << isQuit;
        if (isQuit == "n") {
            isATMworking = true;
        } else if (UsedATM == 'x') {
            myGlobal->Display();
            continue;
        }
        else { isATMworking = false; }
    }
    
    return 0;
}

