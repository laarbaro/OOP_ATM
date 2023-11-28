#include <iostream>
#include <string.h>
#include <map>
#include <vector>
#include <fstream>

using namespace std;

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
        : cardNumber(cardNumber), accountNumber(accountNumber), isAdmin(isAdmin), isBilingual(isBilingual) {}

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

    // 카드가 양 언어 지원으로 구성되어 있는지 확인
    bool isBilingualCard() const {
        return isBilingual;
    }

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
    Card* AdminCard;
    map<string, string> History;
    bool Bilingual = false;
    bool MultiBank = false;
    static int NumberOfATM;
    Session* CurrentSession;

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

    //Get 함수
    int GetSerialNum() { return this->SerialNumber; }
    map<string, Bank*> GetPrimaryBank() { return this->PrimaryBank; }
    map<string, Bank*> GetNonPrimaryBank() { return this->NonPrimaryBank; }
    map<int, int> GetAvailableCash() { return this->AvailableCash; }
    Card* GetAdminCard() { return this->AdminCard; }
    map<string, string> GetHistory() { return this->History; }

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

public:

    Session() : currentTransactionID(1) {}
    void CashDeposit(map<int, int>, int x);
    //void Session::CashDeposit(map<int, int> amount, int x)
    void CheckDeposit(unsigned long long amount, int x);
    void Withdrawal(unsigned long long amount, int x);
    void CashTransfer(map<int, int>, Account* destination, int x);
    void AccountTransfer(unsigned long long amount, Account* destination, int x);
    bool Authorization(string password) {return account->verifyPW(password);}
    
    int GetNextTransactionID() {
        return currentTransactionID++;
    }
    
    
    
    // 여기가 왜 필요할까 ??
    void displayMainKoreanScreen() {
        // getPrimaryBankInfo()의 반환 타입이 map<string, Bank*> 라고 가정
        map<string, Bank*> bankInfo = atm->GetPrimaryBank();

        cout << "\n==================================================" << endl;
        
        // 아래 코드에서 사용할 뱅크 이름을 얻어옵니다.
        string bankName = /* 어떻게든 뱅크 이름을 가져오는 코드 */;
        
        cout  << bankName << " 은행" << endl;

        // 여기서 bankInfo를 사용하여 뱅크 이름에 대한 포인터를 얻어옵니다.
        Bank* bankPtr = bankInfo[bankName];
        
        if (bankPtr->getSingleInfo() == 0) cout << "주거래 은행 전용>" << endl;
        else cout << "타은행 거래 가능>" << endl;
        cout << "--------------------------------------------------\n" << endl;
    }




    
};

//5. Display Class
class Global{
public: 
	Global();
	Global(map<string, Account*>, map );
	~Global();//////////////stop
	
};


/*-------------- Methods of Session Class --------------*/
void Session::CashDeposit(map<int, int> amount, int x) { // 한국어 인지 아닌지

    unsigned long long fee = 0;
    if (!primarySignal) fee = 1000;

    // ATM에 화폐를 추가합니다.
    atm->SetAvailableCash(amount); //plusMoney 가 아닌 다른 함수일 수도 있음 .  임의로 정한 이름임. SetAvailableCash

    // 계좌에 입금합니다.
    unsigned long long totalAmount = 0;
    for (const auto& entry : amount) {
        int denomination = entry.first;
        int count = entry.second;
        totalAmount += (denomination * count);
    }
    int transactionID = GetNextTransactionID();
    account->deposit(totalAmount - fee);

    Transaction CashDepositTransaction(transactionID, card->getCardNumber(), "CashDeposit", totalAmount) ;
    

    
    transctionHistoryOfSession.push_back(CashDepositTransaction);
    
    // 거래 정보를 출력합니다. ~에는 뱅크 이름이랑 어카운트 가져오기 ?
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





void Session::CheckDeposit(unsigned long long amount, int x) {
    unsigned long long fee = 0;
    if (!primarySignal) fee = 1000;
    unsigned long long totalAmount = amount - fee ;
        account->deposit(totalAmount);
    
    
    //ATM에는 안넣음 ??
    
    int transactionID = GetNextTransactionID();
    Transaction CheckDepositTransaction(transactionID, card->getCardNumber(), "CheckDeposit", totalAmount) ;
        
    transctionHistoryOfSession.push_back(CheckDepositTransaction);
    
    // 거래 정보를 출력합니다. ~에는 뱅크 이름이랑 어카운트 가져오기 ?
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





void Session::Withdrawal(unsigned long long amount, int x) { // map을 받아야함.
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
    
    
    if ( totalAvailableCash < amount + fee) {
        if (x == 0) cout << " 현재 기기 내 현금이 부족합니다\n" << endl;
        else cout << " OUR ATM DOESN'T HAVE ENOUGH MONEY\n" << endl;
        
    }
    else if (amount + fee > account->getBalance())  // 졔좌잔액 부족 여부 확인
        if (x == 0) cout << "잔액 부족\n" << endl;
        else cout << " YOU DON'T HAVE ENOUGH MONEY\n" << endl;
    }


    else { // 이제부터 출금 수행 !!
        
        // 출금금액과 수수료를 ATM과 계좌에서 각각 차감
        totalAmount = ammount + fee
        atm->minusMoney(totalAmount); //fee 포함해서 차감 해야하는가 ?  그리고 가능한 돈을 차감하는 함수 이름은 ???
        
        account->withdraw(totalAmount);
        
        int transactionID = GetNextTransactionID();
        
        Transaction withdrawTransaction(transactionID, card->getCardNumber(), "Withdraw", totalAmount) ;
        
        transctionHistoryOfSession.push_back(withdrawTransaction);
        
      
        
        //결과 출력
        // 거래 정보를 출력합니다. ~에는 뱅크 이름이랑 어카운트 가져오기 ?
        if (x == 0)
            cout << "~에 " << totalAmount << " 원이 입금되었습니다." << endl;
        else
            cout << "~에 " << totalAmount << " won has been deposited." << endl;
        
        withdrawalCount ++; // 세션 종료 !! 변수가 있음 ATM에서 가져가면 될듯 ??
        
        if (x == 0) cout << "\n현재 잔액 : ";
        else cout << "\nCURRENT BALANCE : ";
        cout << account->getFundInfo();
        if (x == 0) cout << " 원" << endl;
        else cout << " won" << endl;
        cout << "\n";
    }
}


//이 친구는 뭔가 오류가 많음 ㅠ
void Session::CashTransfer(map<int, int> amount, Account* destination, int x) { //destination는 이체하고 자 하는 계좌.
    
    //fee 보다 적으면 안됨.
    
    //이체 수수료 추가
    unsigned long long fee = 5000 ;
    
    // ATM에게 현금을 추가합니다.
    atm->SetAvailableCash(amount);
    
    
 // 수수료 빼고 계좌에 입금
    for (const auto& entry : amount) {
        int denomination = entry.first;
        int count = entry.second;
        unsigned long long totalAmount = (denomination * count);
    }
    
    unsigned long long totaltotalAmount =  totalAmount - fee
    destination-> deposit ( utotaltotalAmount ) ;
    
    int transactionID = GetNextTransactionID();
    
    Transaction CashTransferTransaction(transactionID, card->getCardNumber(), "CashTransfer", totaltotalAmount) ;
    
    
    transctionHistoryOfSession.push_back(CashTransferTransaction);

    
    // 현재 세션의 거래 내역에도 이체 거래를 추가합니다.
    transactionHistoryOfSession.push_back(newTransaction);

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





// 이친구 history는 다시 손봐야함.
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
    if (amount + fee > account->getFundInfo()) {
        if (x == 0)
            cout << "잔액 부족\n" << endl;
        else
            cout << "YOU DON'T HAVE ENOUGH MONEY\n" << endl;
    } else {
        // 송금 계좌에서 송금액과 수수료를 차감합니다.
        account->minusMoney(amount + fee);

        // 수취 계좌에 송금액을 추가합니다.
        destination->plusMoney(amount);

        // AccountTransferTransaction 클래스의 객체를 생성합니다.
        // 이 객체는 계좌 간 송금 거래에 대한 정보를 담고 있습니다.
        AccountTransferTransaction newTransaction(destination, account, amount, accountNum, destNum);

        // 수취 계좌의 거래 내역에 새로운 거래(newTransaction)를 추가합니다.
        destination->addTransaction(&newTransaction);

        // 송금 계좌의 거래 내역에도 새로운 거래(newTransaction)를 추가합니다.
        account->addTransaction(&newTransaction);

        // 현재 세션의 거래 내역에도 송금 거래를 추가합니다.
        transactionHistoryOfSession.push_back(newTransaction);

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
        
        cout << " 계좌 번호를 입력해주세요\n" << endl;
        cout << "계좌 번호 : ";
        cin >> inputAccount;
        
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
                cout << "비밀번호를 입력해주세요\n" << endl;
                cout << "비밀번호 : ";
                cin >> inputPassword;
                if (Authorization(inputPassword)) {
                    authorizationSignal = true;
                    break;
                }
                else {
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
                        }
                        
                        

                        
                        
                
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
                        if (withdrawalCount == 3) {
                            atm->mainKoreanDisplay();
                            cout << "       세션 1회 당 출금 가능한 액수를 초과하셨습니다\n" << endl;
                        else {
                                
                                
                            }
                        
                        
                        
                        
                        
                    }
                    
                    
                    if (transactionNum == 3) { // 송금
                    }
                    
                    
                    if (transactionNum == 4) { // 거래 내역 조회// Transaction History
                        
                        atm->mainKoreanDisplay();
                        cout << "             거래 내역 조회를 선택하셨습니다\n" << endl;
                        cout << "          해당 계좌의 거래내역은 다음과 같습니다\n" << endl;
                        vector<Transaction> temp = account->getTransactionHistoryOfAccount();
                        if (temp.size() == 0) {
                            cout << "--------------------------------------------------\n" << endl;
                            cout << "            현재 잔액 : " << account->getFundInfo() << " 원\n" << endl;
                            cout << "            해당 계좌에는 거래 내역이 업습니다\n" << endl;
                            cout << "==================================================" << endl;
                        } else {
                            for (int i = 0; i < temp.size(); i++) {
                                cout << temp[i].getKoreanInformation() << endl;
                            }
                            cout << "\n현재 잔액 : " << account->getFundInfo() << " 원\n" << endl;
                            cout << "==================================================" << endl;
                        }
                        
                    }
                    
                    if (transactionNum == 5) { // 서비스 종료
                        
                        sessionExitSignal = false;
                    }
                    
                    
                    
                    
                }
                
                cout << "세션 종료" << endl;
                cout << "ATM을 이용해주셔서 감사합니다\n" << endl;
                if (transactionHistoryOfSession.size() == 0) {
                    cout << "해당 세션에는 거래 내역이 없습니다\n" << endl;
                } else {
                    cout << "               해당 세션 내 총 거래 내역" << endl;
                    
                    atm->addTransaction(transactionHistoryOfSession); //ATM에 넘겨주기.
                    
                    for (int i = 0; i < transactionHistoryOfSession.size(); i++) {
                        cout << transactionHistoryOfSession[i].getKoreanInformation() << endl; // 내역 출력
                    }
                    
                }
            }
        }
    } ; //class 끝
                
                

    void mainKoreanDisplay() {
        cout << atm->getPrimaryBank() << " 은행" << endl;
        if (atm->getSingleInfo() == 0) cout << "주거래 은행 전용>" << endl;
        else cout << "타은행 거래 가능>" << endl;
    }
    
};
class EnglishSession {
public:

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
        CashInATM = CurrentATM->GetAvailableCash();
    };//cash 종류별 개수, bank, username, accountnum, password
    void CheckCheck() {
        CheckInAccount = CurrentAccout->getBalance();
    };//amount, username, accountnum, password
};


//----------------child of Transaction----------------------
class DepositTransaction : public Transaction {
    //아직 미구현: There is a limit in the number of cash or checks that can be deposited per transaction (e.g., 50 papercashes, 30 paper checks)
public:
    string Deposit(ATM* CurrentATM, Account* CurrentAccount, bool isCash, map depositCash//error : map의 타입을 지정하세요) {
        //수수료 책정
        if (CurrentAccount->getBank() == CurrentATM->GetPrimaryBank()) {//error : ==연산자 사용 불가
            int fee = 0;
        }
        else { int fee = 1000; }

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
                available2[available1.first] = available1.second + depositCash[available1.first];//error : available1.first에서 first member가 없다고 하는데 확인해주세요
            }
            CurrentATM->SetAvailableCash(available2);
        }

        //account 액수 증가
        CurrentAccount->Deposit(depositCash_sum + fee);//error : fee가 정의되어있지 않습니다

            //history return
            return "cash deposit KRW " + to_string(depositCash_sum) + "(balance now: KRW " + to_string(CurrentAccount->getBalance()) + ")";//error : to_string이 정의되어있지 않습니다
    };
};

class withdrawTransaction : public Transaction {
public:
    string Withdraw(ATM* CurrentATM, Account* CurrentAccount, int Amount) {
        //bank에서 계좌 확인 후 limit 안넘으면 출금, bank 확인해 fee 결정해 빼고 출금, ATM의 available_cash 감소, 최대 50만원 withdraw 가능
        //수수료 책정
        if (CurrentAccount->getBank() == CurrentATM->GetPrimaryBank()) {
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
            for (const auto& entry : AvailableNow) {
                AvailableUpdate[AvailableNow.first] = AvailableNow.second - out[AvailableNow.first];//error : first 멤버가 없습니다
            }
            CurrentATM->SetAvailableCash(AvailableUpdate);

            //Account balance 감소
            CurrentAccount->Withdraw(Amount + fee);//error : fee가 정의되어있지 않습니다

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
            if (Account1->getBank() == CurrentATM->GetPrimaryBank() && Account2->getBank() == CurrentATM->GetPrimaryBank()) {//error : ==연산자 사용 불가
                int fee = 3000;
            }
            else if (Account1->getBank() == CurrentATM->GetPrimaryBank() || Account2->getBank() == CurrentATM->GetPrimaryBank()) {//error : ==연산자 사용 불가
                int fee = 4000;
            }
            else { int fee = 5000; }

            Account1->Withdraw(Amount + fee);//error : fee가 정의되어있지 않습니다 //error : 
            Account2->Deposit(Amount);

            //return history
            return "cash transfer KRW " + to_string(Amount) + ", from " + Account1->getAccountNum() + " to " + Account1->getAccountNum() + "(balance now: KRW" + to_string(CurrentAccount->getBalance()) + ")";//error : to_string이 정의되어있지 않습니다
        }
        else { // 잔액부족
            return "error: The user ordered transfer of an amount that exceeds the amount currently available from the account.";
        };
    };

    string CashTransfer(ATM* CurrentATM, Account* Account1, Account* Account2, map Cash) {//error : map의 type이 정의되어있지 않습니다(ex. map<int,int> Cash)
        int Cash_sum = 0;
        for (const auto& entry : Cash) {
            Cash_sum += entry.first * entry.second;
        }

        //transfer 가능한가?
        if (Account1->getBalance() >= Cash_sum) {
            if (Cash_sum == 5000) {
                //수수료 책정
                if (Account1->getBank() == CurrentATM->GetPrimaryBank() && Account2->getBank() == CurrentATM->GetPrimaryBank()) {
                    int fee = 3000;
                }
                else if (Account1->getBank() == CurrentATM->GetPrimaryBank() || Account2->getBank() == CurrentATM->GetPrimaryBank()) {
                    int fee = 4000;
                }
                else { int fee = 5000; }

                Account1->Withdraw(Cash_sum);
                Account2->Deposit(Cash_sum);

                //return history
                return "cash transfer KRW " + to_string(Amount) + ", from " + Account1->getAccountNum() + " to " + Account1->getAccountNum() + "(balance now: KRW" + to_string(CurrentAccount->getBalance()) + ")";//error : CurrentAccount에 액세스할 수 없습니다, to_string이 정의되어 있지 않습니다, Amount가 정의되어있지 않습니다}
            else {
                return "error: The amount came in ATM is not KRW 5000.";
            }
	        else { // 잔액부족
	            return "error: The user ordered transfer of an amount that exceeds the amount currently available from the account.";
	        }//error : if문이 필요합니다
	    };
	};
    };
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
};

    // Bank 클래스의 소멸자
    ~Bank() {
    // 소멸자에서 리소스 정리 작업 수행
    // 예: 동적으로 할당된 메모리 해제 등
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
	        	} 
	        	else {
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
bool CheckInvalidCard(int cardnum, int pw){
	 ///////////////////////////////이 부분 어떻게 할지, bank에서 카드 맵 저장하는게 나을지도
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
        }
        else {
            this->CurrentSession = new KoreanSession();
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



//-------------------------------------Transaction---------------------------------------
/*
void Transaction::Withdraw(int, string, string, int, string) {
    // 현금 확인하여 인출가능 금액인지 확인
	
    //amount, bank, username, AccountNum, password
    //bank에서 계좌 확인 후 limit 안넘으면 출금, bank 확인해 fee 결정해 빼고 출금, ATM의 available_cash 감소, 최대 50만원 withdraw 가능
    cout << "출금하실 금액을 입력하세요." << endl;
    cin >> int w;
    if (w < account.getBalance()) {
        cout << "잔액이 부족합니다." << endl;
    }


	else {
		map<int, int> ATM_AvailableCash = this->CurrentATM->get_AvailableCash();
		//현금 권수에 따른 계산 필요
	}

	
}
void Transaction::Transfer(string, string, int, string, string, int) {
	//bank1, username, AccountNum, password, bank2, amount
	//fee 고려, amount+fee 잔액 확인
	cout << "이체하실 금액을 입력하세요." << endl;
	cin >> int t;
	cout << "출금하실 계좌번호를 입력하세요." << endl;
	cin >> int acc_out;
	cout << "입금하실 계좌번호를 입력하세요." << endl;
	cin >> int acc_in;
	if (t > limit) {
	        cout << "입금가능한 금액을 초과하였습니다." << endl;
	}
	else {
		acc_out.Deposit(t+fee);
	        acc_in.Withdraw(t);
	        cout << t << "원 송금이 완료되었습니다." << endl;
	}
}
void Transaction::Open_Account(string, string, int, string, int) {
	//bank, username, AccountNum, password, (account number->있었는데 삭제, available fund
	cout << "은행 이름을 입력하세요." << endl;
	cin << string bankName << endl;
	cout << "사용자 이름을 입력하세요." << endl;
	cin << string userName << endl;
	cout << "비밀번호를 입력하세요." << endl;
	cin << int pw << endl;
	Account(bankName, userName, pw);
}
void Transaction::Deposit(int, account*) {
    //Receiving Account
	cout << "====================Cash Deposit====================" << endl;
	cout << "Which Bank do you want to deposit?" << endl;
	cin >> Bank1;
	cout <<"What is your name?" << endl;
	cin >> Username1;
	cout << "Please write your Account Number and Password" << endl;
	cin >> AccountNum1, Password1;
	
	cout << "Authorizing your account..." << endl;
	if Authorize(Username1, AccountNum1, Password1) {
	        cout << "Successfully Authorized Your Account!" << endl;  
	        //Saving Cash
	        if (Bank1 == this->PrimaryBank){
	            Bank1->getAccount(AccountNum1)->Amount += InputAmount; 
	        }else{
	            Bank1->getAccount(AccountNum1)->Amount += (InputAmount-this->2_DP);
	        }
	        cout << "Successfully Deposited!" << endl;
	        cout << "Bank : " << Bank1->getName();
	        cout << " Account Number : " << AccountNum1;
	        cout << " Total Amount of Saving : " << Bank1->getAccount(AccountNum1)->Deposit(InputAmount) << endl;
	} else {
	        cout << "Failed to Deposit." << endl;
	}
	cout << "===Thanks for Using Deposit Service of this ATM====" << endl;
	}

}
*/
Transaction::CheckCash() {
//declaration
    	map<int, int>inputmap;
    	int NumCash1;
    	int i,j;
    	Bank* Bank1;
    	string Username1;
    	string AccountNum1;
    	string Password1;
    	int InputAmount = 0;
    	int SavingAmount = 0;
	//Receiving Cash
	cout << "====================Cash Insert====================" << endl;
	cout << "How many cash do you want to insert?" << endl;
	cin >> NumCash1;
	for (int i=0; i<NumCash1; i++){
		cout << "Insert your cash(Unit, Number of the cash by type)" << endl;
	        cin >> i,j;
	        inputmap.insert(pair<int, int>(i, j));
	}
    
	for (int iter = inputmap.begin() ; iter !=  inputmap.end(); iter++){ //error
	        InputAmount+=(iter->second * iter->first);//원화 단위 * 개수     
	};
	
};
Transaction::CheckCheck() {
	//declaration
    	int NumCheck2;
   	int inputCheck;
    	Bank* Bank2;
    	string Username2;
    	string AccountNum2;
    	string Password2;
    	int InputAmount2 = 0;
    	int SavingAmount2 = 0;

    	//Receiving Cash
    	cout << "====================Cash Insert====================" << endl;
    	cout << "How many check do you want to insert?" << endl;
    	cin >> NumCheck2;
    	for (int i=0; i<NumCheck2; i++){
        	cout << "Insert your check" << endl;
        	cin >> inputCheck;
        	InputAmount2 += inputCheck;
    	}

    
};
/*
Transaction::Display(int TransactionAmount, string Username, AccountNum, CardNum, myBank, ExternalFile=false){
//이름 받아 transaction 결과 보여줌, 각 transaction에서 호출, external file True면 external file로 출력

    	cout << "=================Transaction Result=================" << endl;
    	cout << "User Name : " << Username << endl;
    	cout << "Account : " << AccountNum << endl;
    	cout << "Card : " << CardNum << endl;
    	cout << "From "<< myBank << " " << TransactionAmount << "Won" << endl;
}

Transaction::Authorize(string Username, int AccountNum, string Password, Bank* Bank){
    	string UsernameFromBank = Bank->getAccount(AccountNum)->getUserName
    	string UserPassword = Bank->getAccount(AccountNum)->getPassword
    	if (UsernameFromBank==Username){
        	if (UserPassword==password){
            		return True;
        	}else{
            		return False;
        	}
    	}else{
		cout << "Authorizing Fail" << endl;
        	return False;
    	};
    
};
*/




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
	//[수정 필요]논의 후 수정
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
		ATMmap[UsedATM]->Start();

		//quit?
		char isQuit;
		cout << "Do you want to terminate current program? (y, n)" << endl;
		cin << isQuit;
		if (isQuit == "n") {
			isATMworking = true;
		}
		else { isATMworking = false; }
	}

		
	return 0;
}
