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


// -------------------------------[Session] class-----------------------------------
// -------------------------------[Session] class-----------------------------------
class Session {
private:
    ATM* atm; // ATM 객체 가리키는 포인터
    Account* account; // 계좌 객체 가리키는 포인터
    vector<Transaction> transctionHistoryOfSession; // 세션 동안 거래 내역 저장 -> 하고 뭐햇는지 display 해야함. 하나 저장 후 보여주기 (이걸 함수로먼들지 그냥 코드를 짤지는선택 ) + 백터 구조가 어떤지 알려줘서 ATM에 할수 있게 하기
    bool authorizationSignal; // 계좌 비밀번호 인증 결과 나타내는 bool값
    int aouthorizationCount; // 비밀번호 인증 실패 횟수
    int withdrawalCount; // 출금 횟수 기록
    bool primarySignal; // 현재 계좌 은행 정보와 ATM 주거래 은행이 동일한지 여부를 나타내는 bool 값

public:
    /*
        void Open_Account(string, string, int, string, int, int); //bank, username, AccountNum, password, account number, available fund
        void Display(int, string, int, int, string, bool); //이동한 금액, username, AccountNum, card number, bank, externalFile=False 필요여부//이름 받아 transaction 결과 보여줌, 각 transaction에서 호출, external file True면 external file로 출력
        void Authorize(int, string, int); //card number, username, AccountNum//함수 내에서 password 요구 및 확인 필요, 최대 3번 요구 후 return card
    */
    Session() {}
    void CashDeposit(unsigned long long amount, int x);
    void CheckDeposit(unsigned long long amount, int x);
    void Withdrawal(unsigned long long amount, int x);
    void CashTransfer(unsigned long long amount, Account* destination, int x);
    void AccountTransfer(unsigned long long amount, Account* destination, int x);
    bool Authorization(string password) { return account->check_pw(password); }

};


// History에서 withdraw 3번 넘으면 session 종료

// -------------child of Session class ---------------
class KoreanSession : public Session {
public:
    KoreanSession(ATM* iatm) {
        atm = iatm;
        primarySignal = true;
        authorizationCount = 0;
        withdrawalCount = 0;
        authorizationSignal = true;

        bool validAccount = true; // 계좌 정보 유무 
        string inputAccount;
        atm-> ? ? (); //ATM 객체의 어떤 메서드호출하여 한국어로 메인 화면을 출력 (     " << this->getPrimaryBankInfo() " 은행" 출력 ,  if (this->getSingleInfo() == 0) -> 주은행 거래만 가능  else "타은행 거래 가능" 출력 )

        cout << " 계좌 번호를 입력해주세요\n" << endl;
        cout << "계좌 번호 : ";
        cin >> inputAccount;

        if (findAccount(inputAccount) == nullptr) {
            atm-> ? ? (); ////ATM 객체의 어떤 메서드호출하여 한국어로 메인 화면을 출력
            cout << "입력한 계좌번호가 존재하지 않습니다." << endl;
            validAccount = false;
        }
        else {
            Bank* temp = findAccount(inputAccount); //findAccount 함수를 사용하여 입력된 계좌 번호에 해당하는 Bank 객체를 찾아서 temp 포인터에 저장
            if ((atm->getPrimaryBankInfo()).compare(temp->getBankName()) == 0) { //현재 세션에서 사용 중인 ATM 객체(atm)의 기본 은행 정보와, 입력된 계좌 번호에 해당하는 Bank 객체의 은행 이름을 비교 ! 두 은행 이름이 같다면, 현재 세션에서 사용 중인 은행이라는 것을 의미
                account = temp->findAccountOfBank(inputAccount); //같다면, 해당 은행에서 입력된 계좌 번호에 해당하는 Account 객체를 찾아서 account 포인터에 저장합니다. 이렇게 하면 현재 세션에서 사용할 수 있는 계좌를 설정
            }
            else {
                if (atm->IsMultiBank() == false) { //타은행 계좌를 사용할 수 없다면
                    atm-> ? ? ();
                    cout << "타은행 계좌는 사용하실 수 없습니다\n" << endl;
                    validAccount = false;
                }
                else {
                    primarySignal = false;
                    account = temp->findAccountOfBank(inputAccount);
                }
            }
        }

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
    string Deposit(ATM* CurrentATM, Account* CurrentAccount, bool isCash, map depositCash) {
        //수수료 책정
        if (CurrentAccount->getBank() == CurrentATM->GetPrimaryBank()) {
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
                available2[available1.first] = available1.second + depositCash[available1.first];
            }
            CurrentATM->SetAvailableCash(available2);
        }

        //account 액수 증가
        CurrentAccount->Deposit(depositCash_sum + fee);

            //history return
            return "cash deposit KRW " + to_string(depositCash_sum) + "(balance now: KRW " + to_string(CurrentAccount->getBalance()) + ")";
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
                AvailableUpdate[AvailableNow.first] = AvailableNow.second - out[AvailableNow.first];
            }
            CurrentATM->SetAvailableCash(AvailableUpdate);

            //Account balance 감소
            CurrentAccount->Withdraw(Amount + fee);

            //history return
            return "cash withdrawal KRW " + to_string(Amount) + "(balance now: KRW" + to_string(CurrentAccount->getBalance()) + ")";

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
            if (Account1->getBank() == CurrentATM->GetPrimaryBank() && Account2->getBank() == CurrentATM->GetPrimaryBank()) {
                int fee = 3000;
            }
            else if (Account1->getBank() == CurrentATM->GetPrimaryBank() || Account2->getBank() == CurrentATM->GetPrimaryBank()) {
                int fee = 4000;
            }
            else { int fee = 5000; }

            Account1->Withdraw(Amount + fee);
            Account2->Deposit(Amount);

            //return history
            return "cash transfer KRW " + to_string(Amount) + ", from " + Account1->getAccountNum() + " to " + Account1->getAccountNum() + "(balance now: KRW" + to_string(CurrentAccount->getBalance()) + ")";
        }
        else { // 잔액부족
            return "error: The user ordered transfer of an amount that exceeds the amount currently available from the account.";
        };
    };

    string CashTransfer(ATM* CurrentATM, Account* Account1, Account* Account2, map Cash) {
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
                return "cash transfer KRW " + to_string(Amount) + ", from " + Account1->getAccountNum() + " to " + Account1->getAccountNum() + "(balance now: KRW" + to_string(CurrentAccount->getBalance()) + ")";
            }
            else {
                return "error: The amount came in ATM is not KRW 5000.";
            }
        else { // 잔액부족
            return "error: The user ordered transfer of an amount that exceeds the amount currently available from the account.";
        }
    };
};



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
    void OpenSession();

    //Set 함수
    void SetAvailableCash(map);

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



// -------------------------------[Card] class-----------------------------------
// -------------------------------[Card] class-----------------------------------

///황지영

class Card {
    //admin 여부, bank, account 정보

private:
    string cardNumber;
    string accountNumber;
    bool isAdmin;
    bool isBilingual; // 양 언어 구성이 카드와 관련이 있다고 가정

public:
    // 생성자
    Card(const string& cardNumber, const string& accountNumber, bool isAdmin, bool isBilingual)
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


// -------------------------------[Bank] class-----------------------------------
// -------------------------------[Bank] class-----------------------------------

class Account; //전방 선언 

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

    // 계좌 존재 여부 확인 (주어진 계좌 번호가 은행에 존재하는지 여부를 확인하는 함수)
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








///--------------------------------method-------------------------------------

///--------------------------------method-------------------------------------

///--------------------------------method-------------------------------------

/*-------------- Methods of Session Class --------------*/
void Session::CashDeposit(map<int, int> amount, int x) { // 한국어 인지 아닌지

    unsigned long long fee = 0;
    if (!primarySignal) fee = 1000;

    // ATM에 화폐를 추가합니다.
    atm->plusMoney(amount);

    // 계좌에 입금합니다.
    unsigned long long totalAmount = 0;
    for (const auto& entry : amount) {
        int denomination = entry.first;
        int count = entry.second;
        totalAmount += (denomination * count);
    }
    account->plusMoney(totalAmount - fee);

    // 거래를 생성하고 계좌에 추가합니다.

    //////////////////// 이부분 !!
   ///////////////DepositTransaction클래스에 새 객체 생성 .
    DepositTransaction newTransaction(account, amount, findAccount(account->getAccountNumber())->getBankName());




    //(계좌, 현금 ( 맵 ) , 뱅크 이름)
    account->addTransaction(&newTransaction); // 계좌자체의 거래내역.
    // 계좌에 새 거래 추가 *addTrnascation은 account의 함수.

    transactionHistoryOfSession.push_back(newTransaction); //세션 전체 동안의 거래 내역
    // 거래 정보를 출력합니다.

    if (x == 0) cout << newTransaction.getKoreanInformation() << endl;
    else cout << newTransaction.getEnglishInformation() << endl;

    // 현재 잔액을 출력합니다.
    if (x == 0) cout << "/n현재 잔액 : ";
    else cout << "\nCurrent Available Cash : ";
    cout << account->getBalance();

    if (x == 0) cout << " 원" << endl;
    else cout << " won" << endl;

    cout << "\n";
}


void Session::CheckDeposit(unsigned long long amount, int x) {
}

void Session::Withdrawal(unsigned long long amount, int x) {
}


void Session::CashTransfer(unsigned long long amount, Account* destination, int x) {
}

void Session::AccountTransfer(unsigned long long amount, Account* destination, int x) {
}




//-------------------------------------ATM-------------------------------------------
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
    //언어 받고 session열어주기
    //ATM 초기 잔고 보여주기 받기
    //account 개설 받기 -> transaction에서 하던데
    //카드 입력하세요 후 CheckAdmin()후 session 열어주기
    //admin card면 transaction history 볼 수 있게 열어주기
    //transaction history에서는 모든 transaction 보여주기, user명과 transaction id, card num, transaction type, amount 등 정보
    //필요시 파일로 transaction history 뽑기
    //카드 invalid 확인해서 error 띄우기
    //카드 return 표시하기
    //ATM 잔고 보여주기

    cout << "Welcome" << endl;
    cout << "To start a session, please insert your debit card" << endl;
    int CN, PW;
    cout << "Insert card number and password" << endl;
    if (CheckAdmin(CN, PW)) {
        int sel;
        cout << "Welcome Administrator" << endl;
        cout << "[1] Show me history [etc] Show me Available Cash" << endl;
        cin >> sel;
        if (sel == 1) {
            ShowHistory();
        }
        else {
            ShowAvailableCash();
        }
    }
    else {
        OpenSession();
    };
};
bool CheckAdmin(int cardnum, int pw) {
    return this->AdminCard->isAdminCard(cardnum, pw);
};
bool OpenSession() {
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
void SetAvailableCash(map<int, int> inputcash) {
    for (auto iter = this->AvailableCash.begin(); iter != this->AvailableCash.end(); iter++) {
        int currentnum = inputcash.find(iter->first)->second;
        iter->second += currentnum;
    };
};
void ShowHistory() {
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
/*여기 좀 수정했습니다
    else if (AvailableCash < w) {
        cout << "기기의 인출 가능 금액이 부족합니다. 관리자에게 문의하세요." << endl;
    }
    else {
        account.Withdraw(w+fee);
        AvailableCash -= w;
        withdrawalN--;
        cout << w << "원이 인출되었습니다." << endl;
    }
	*/

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
	        inputmap.insert({i, j});
	}
    
	for (int iter = inputmap.begin() ; iter !=  inputmap.end(); iter++){
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
		Account(AccountNum, pw, ownername, ); //수정중

		//Card 선언
		//적어도 admin card는 여기에서 선언되어 ATM을 생성할 때 넣어줘야 함.
		cout << "카드를 만드시겠습니까? (y, n)" << endl;
		cin >> char makeCard;
		if (makeCard == "y") {
			cout << "카드번호를 입력하세요" << endl;
			cin >> int cardNumber;
			cout << "관리자 권한을 부여하시겠습니까? (y, n)" << endl;
			cin >> char askAdmin;
			if (askAdmin = "y") { bool isAdmin = true; }
			else { bool isAdmin = false; }
			
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
		ATMmap.insert({ATMname, new ATM(InputBankMap.find(InputPrimaryBank), InputBankMap, AdminCard);
	}
		
	
    // 지영 예제 사용법:
	
    Bank myBank;

    // 계정 생성 및 추가
    myBank.createAccount("123", "password123", "JohnDoe");
    myBank.createAccount("456", "pass456", "JaneDoe");
    myBank.allAccount("JohnDoe"); // JohnDoe의 계정 출력

    // 사용자 및 계정 확인
    if (myBank.verifyUser("JohnDoe", "123", "password123")) {
        std::cout << "사용자 확인 성공." << std::endl;
    } else {
        std::cout << "사용자 확인 실패." << std::endl;
    }

    if (myBank.verifyAccount("123", "password123")) {
        std::cout << "계정 확인 성공." << std::endl;
    } else {
        std::cout << "계정 확인 실패." << std::endl;
    }

    return 0;
}




