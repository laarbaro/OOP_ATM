#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>

using namespace std;

class Global;
class ATM;
class Session;
class Card;
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

public:
    // 생성자
    Card(const string& cardNumber, const string& accountNumber)
        : cardNumber(cardNumber), accountNumber(accountNumber) {}

    // 카드 번호를 가져오는 함수
    const string& getCardNumber() const;

    // 계정 번호를 가져오는 함수
    const string& getAccountNumber() const;

    // 카드가 관리자 카드인지 확인
    //[유리] card number와 password를 받아서 Admin인지 확인해주세요
    /*
        // 카드가 양 언어 지원으로 구성되어 있는지 확인
        bool isBilingualCard() const {
            return isBilingual;
        }
    */
    // 카드 유효성 검사, 인증과 관련된 다른 함수들도 추가할 수 있음
};
const string& Card::getCardNumber() const { return cardNumber; }
const string& Card::getAccountNumber() const { return accountNumber; }



//Bank
class Bank {
private:
    map<string, Account*> accounts; // 계좌 번호를 키로 사용
    string bankName;

public:

    Bank(string name) : bankName(name) {}; // Bank name 설정

    // 현재 account 있는지 확인하 없으면 생성
    void createAccount(string, string, string);

    // 사용자 정보를 모두 출력하는 함수 (특정 사용자의 모든 계정 정보를 출력하는 함수)
    void allAccount(string username);

    // 사용자 정보를 확인하는 함수 (사용자 정보를 확인하고, 주어진 사용자 이름, 계좌 번호, 비밀번호와 일치하는지 여부를 반환하는 함수)
    bool verifyUser(string username, string accountNum, string password);

    // 계정 정보를 확인하는 함수(계정 정보를 확인하고, 주어진 계좌 번호와 비밀번호가 일치하는지 여부를 반환하는 함수)
    bool verifyAccount(string accountNum, string password);

    // 계좌 존재 여부 확인 (주어진 계좌 번호가 은행에 존재하는지 여부를 확인하는 함수) //Account의 pointer를 반환하면?
    bool accountExists(string accountNum);


    // 은행 이름 리턴 함수
    string getBankName() { return bankName; };

    // Bank 클래스의 소멸자
    ~Bank() {}
    // 소멸자에서 리소스 정리 작업 수행
    // 예: 동적으로 할당된 메모리 해제 등

    void setAccounts(map<string, Account*> inputAcc) {
        for (const auto& pair : inputAcc) { this->accounts[pair.first] = pair.second; }
    };
    map<string, Account*> AccountsInBank() { return accounts; };
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
    long long int balance;
    Bank* myBank; // Bank 클래스의 전방 선언 사용 ,  포인터 연결은 여기서 해주는게 맞음
    Card* myCard;

public:
    // 생성자: AccountNum, Password, OwnerName 설정
    Account(const string& accountNum, const string& password, const string& ownerName, Bank* bank)
        : accountNum(accountNum), password(password), ownerName(ownerName), myBank(bank), balance(0) {}

    // Password 검증 함수
    bool verifyPW(const string& enteredPassword) const;

    // AccountNum 반환 함수
    const string& getAccountNum() const;

    // OwnerName 반환 함수
    const string& getOwnerName() const;

    // Bank 반환 함수
    Bank* getBank() const;

    // Bank 이름 반환 함수
    string getBankName() const;

    //card pointer
    Card* getMyCard() { return myCard; };
    void setMyCard(Card* crd) { myCard = crd; };

    // 잔액 조회 함수
    int getBalance() const;

    // 입금 함수
    void deposit(int amount);

    // 출금 함수
    void withdraw(int amount);
};


// 현재 account 있는지 확인하 없으면 생성
void Bank::createAccount(string accountNum, string password, string ownerName) {
    if (!accountExists(accountNum)) {
        accounts[accountNum] = new Account(accountNum, password, ownerName, this);
    }
}

// 사용자 정보를 모두 출력하는 함수 (특정 사용자의 모든 계정 정보를 출력하는 함수)
void Bank::allAccount(string username) {
    cout << "사용자 " << username << "의 모든 계정 정보:" << endl;
    for (auto entry : accounts) {
        if (entry.second->getOwnerName() == username) {
            cout << "계좌 번호: " << entry.second->getAccountNum() << ", ";
            cout << "잔액: " << entry.second->getBalance() << endl;
        }
    }
}

// 사용자 정보를 확인하는 함수 (사용자 정보를 확인하고, 주어진 사용자 이름, 계좌 번호, 비밀번호와 일치하는지 여부를 반환하는 함수)
bool Bank::verifyUser(string username, string accountNum, string password) {
    auto it = accounts.find(accountNum);
    if (it != accounts.end()) {
        Account* account = it->second;
        return (account->getOwnerName() == username && account->verifyPW(password));
    }
    return false; // 사용자 확인 실패
}

// 계정 정보를 확인하는 함수(계정 정보를 확인하고, 주어진 계좌 번호와 비밀번호가 일치하는지 여부를 반환하는 함수)
bool Bank::verifyAccount(string accountNum, string password) {
    auto it = accounts.find(accountNum);
    return (it != accounts.end() && it->second->verifyPW(password));
}

// 계좌 존재 여부 확인 (주어진 계좌 번호가 은행에 존재하는지 여부를 확인하는 함수) //Account의 pointer를 반환하면?
bool Bank::accountExists(string accountNum) {
    return { accounts.find(accountNum) != accounts.end() };
}


// Password 검증 함수
bool Account::verifyPW(const string& enteredPassword) const {
    return (this->password == enteredPassword);
}
// AccountNum 반환 함수
const string& Account::getAccountNum() const {
    return accountNum;
}
// OwnerName 반환 함수
const string& Account::getOwnerName() const {
    return ownerName;
}
// Bank 반환 함수
Bank* Account::getBank() const {
    return myBank;
}
// Bank 이름 반환 함수
string Account::getBankName() const {
    return myBank->getBankName();
};
// 잔액 조회 함수
int Account::getBalance() const {
    return balance;
}
// 입금 함수
void Account::deposit(int amount) {
    balance += amount;
}
// 출금 함수
void Account::withdraw(int amount) {
    if (amount <= balance) {
        balance -= amount;
    }
    else {
        cout << "잔액이 부족합니다. 이 cout은 출력되지 않는 것이 좋습니다." << std::endl; //stop
    }
}

//3. ATM Class
// -------------------------------[ATM] class-----------------------------------
// -------------------------------[ATM] class-----------------------------------
class ATM {
private:
    int SerialNumber;
    map<string, Bank*> PrimaryBank;
    map<string, Bank*> NonPrimaryBank;
    map<int, int> AvailableCash;//현금 단위, 갯수
    unsigned long long AvailableCashAmount;//현금 양
    string AdminCard;
    vector<string> History;
    bool Bilingual = false;
    bool MultiBank = false;
    static int NumberOfATM;
    Session* CurrentSession;
    Global* myGlobal;

public:
    ATM();
    ATM(Bank* pb, map<string, Bank*> allb, string admin);//primary bank pointer, allbankmap, admincard
    ~ATM();
    void Start();
    bool CheckAdmin();
    bool CheckInvalidCard();
    void OpenSession();

    //Set 함수
    void SetSerialNumber(int serial) { this->SerialNumber = serial; };
    void SetAvailableCash(map<int, int>, bool);
    void SetGlobal(Global* inglobal) { this->myGlobal = inglobal; };
    void SetHistory(string newTransaction) { this->History.push_back(newTransaction); };

    //Get 함수
    int GetSerialNum() { return this->SerialNumber; }
    map<string, Bank*> GetPrimaryBank() { return this->PrimaryBank; }
    map<string, Bank*> GetNonPrimaryBank() { return this->NonPrimaryBank; }
    map<int, int> GetAvailableCash() { return this->AvailableCash; }
    string GetAdminCard() { return this->AdminCard; }
    vector<string> GetHistory() { return this->History; }
    unsigned long long GetAvailableCashAmount() { return this->AvailableCashAmount; }
    Global* GetMyGlobal() { return this->myGlobal; }


    //Is 함수
    bool IsMultiBank() { return this->MultiBank; }
    bool IsMBilingual() { return this->Bilingual; }


    //Show 함수
    void ShowHistory();
    void ShowAvailableCash();

    bool CheckInvalidCard(string, string);
    bool CheckAdmin(string);
};


//Global class
class Global {
private:
    map<string, ATM*> ATMMap;
    map<string, Account*> AccountMap;
public:
    Global(map<string, Account*> mpa, map<string, ATM*> mpb) : AccountMap(mpa), ATMMap(mpb) {};
    void setAccountMap(map<string, Account*> inmap);
    void setATMMap(map<string, ATM*> inmap);
    void Display();
    map<string, ATM*> getATMMap() { return ATMMap; };
    map<string, Account*> getAccountMap() { return AccountMap; };
};


//4. Session Class
// -------------------------------[Session] class-----------------------------------
// -------------------------------[Session] class-----------------------------------
class Session {
    //private:
protected:
    ATM* atm; // ATM 객체 가리키는 포인터
    Account* account; // 계좌 객체 가리키는 포인터
    Card* card;
    vector<string> transctionHistoryOfSession; // 세션 동안 거래 내역 저장 -> 하고 뭐햇는지 display 해야함. 하나 저장 후 보여주기 (이걸 함수로먼들지 그냥 코드를 짤지는선택 ) + 백터 구조가 어떤지 알려줘서 ATM에 할수 있게 하기
    bool authorizationSignal; // 계좌 비밀번호 인증 결과 나타내는 bool값
    int authorizationCount; // 비밀번호 인증 실패 횟수
    bool validAccount;   // 계좌번호 확인결과
    int withdrawalCount; // 출금 횟수 기록
    bool primarySignal;  // 현재 계좌 은행 정보와 ATM 주거래 은행이 동일한지 여부를 나타내는 bool 값
    int currentTransactionID;
    Global* myGlobal;

public:
    Session() : currentTransactionID(1) {}
    void CashDeposit(map<int, int>, int x);
    //void Session::CashDeposit(map<int, int> amount, int x)
    void CheckDeposit(unsigned long long, int x);
    void Withdrawal(const map<int, int>&, int x);
    void CashTransfer(map<int, int>, Account*, int x);
    void AccountTransfer(unsigned long long, Account*, int x);
    bool Authorization(string password) { return account->verifyPW(password); };
    int GetNextTransactionID() { return currentTransactionID++; };
    void SetmyGlobal(Global* inputglo) { myGlobal = inputglo; };
    virtual void VerifyAccountNum() = 0;
    virtual void AuthorizePassword() = 0;
    vector<string> GetSessionHistory() { return transctionHistoryOfSession; };
};

/*-------------- Methods of Session Class --------------*/

//1. 현금 입금 함수
void Session::CashDeposit(map<int, int> amount, int x) { //x=0이면 한국어

    //Primary bank인지 확인하고 fee를 결정합니다.
    unsigned long long fee = 0;
    if (!primarySignal) fee = 1000;
    // ATM에 화폐를 추가합니다.
    atm->SetAvailableCash(amount, true);  // ATM에 돈을 추가하는거면 true, 빼는 거면 false
    // amount map에 있는 돈의 총량을 계산하고 계좌에 입금합니다.
    unsigned long long totalAmount = 0;
    for (const auto& entry : amount) {
        int denomination = entry.first;
        int count = entry.second;
        totalAmount += (denomination * count);
    }
    int transactionID = GetNextTransactionID();
    cout << totalAmount - fee << endl;
    account->deposit(totalAmount - fee);

    //History를 저장합니다.
    //형식 : [1] Transaction ID: 1234, Card number: 234, Transaction type: Cash deposit, Amount: 2347, Deposit account number: 23478
    string out = "[";
    out += to_string(atm->GetHistory().size());
    out += "] Transaction ID: ";
    out += to_string(this->currentTransactionID);
    out += ", Card number: ";
    out += account->getMyCard()->getCardNumber();
    out += ", Transaction type: Cash deposit, Amount: ";
    out += to_string(totalAmount);
    out += ", Deposit account number: ";
    out += account->getAccountNum();
    atm->SetHistory(out);
    this->transctionHistoryOfSession.push_back(out);


    /////question) History가 string으로 바뀌어 업데이트 했습니다. 삭제해도 될까요?
    // ------[history 관리]
    //Transaction CashDepositTransaction(transactionID, card->getCardNumber(), "CashDeposit", totalAmount) ;
    //transctionHistoryOfSession.push_back(CashDepositTransaction);
    //------



    // 거래 정보를 출력합니다.
    if (x == 0)//
        //출력 형태 : "Kakao 은행의 계좌 020202(계좌번호)에 3000원이 입금되었습니다."
        cout << account->getBankName() << " 은행의 계좌 " << account->getAccountNum() << "에 " << totalAmount << "원이 입금되었습니다." << endl;
    else
        //출력 형태 : "3000 won has been deposited into the account 020202 of Kakao Bank."
        cout << totalAmount << "won has been deposited into the account " << account->getAccountNum() << " of " << account->getBankName() << " Bank." << endl;

    // 현재 잔액을 출력합니다.
    if (x == 0)
        //출력 형태 : "현재 잔액 : 3000 원"
        cout << "현재 잔액 : ";
    else
        //출력 형태 : "Current Available Cash : 3000 won"
        cout << "Current Available Cash : ";
    cout << account->getBalance();

    if (x == 0) cout << " 원" << endl;
    else cout << " won" << endl;

    cout << "\n";
}




// 2. 수표를 입금해주는 함수
void Session::CheckDeposit(unsigned long long amount, int x) {

    // Primary bank인지 확인하고 fee를 결정합니다.
    unsigned long long fee = 0;
    if (!primarySignal) fee = 1000;

    // 계좌에 입금합니다.
    unsigned long long totalAmount = amount - fee;
    account->deposit(totalAmount);
    int transactionID = GetNextTransactionID();

    //질문 , ATM에는 돈을 안넣나요. ? 네!!

    //History를 저장합니다.
    //형식 : [1] Transaction ID: 1234, Card number: 234, Transaction type: Cash deposit, Amount: 2347, Deposit account number: 23478
    string out = "[";
    out += to_string(atm->GetHistory().size());
    out += "] Transaction ID: ";
    out += to_string(this->currentTransactionID);
    out += ", Card number: ";
    out += account->getMyCard()->getCardNumber();
    out += ", Transaction type: Check deposit, Amount: ";
    out += to_string(totalAmount);
    out += ", Deposit account number: ";
    out += account->getAccountNum();

    atm->SetHistory(out);
    this->transctionHistoryOfSession.push_back(out);

    //Transaction CheckDepositTransaction(transactionID, card->getCardNumber(), "CheckDeposit", totalAmount) ;
    //transctionHistoryOfSession.push_back(CheckDepositTransaction);
    //-------------------

    // 거래 정보를 출력합니다.
    if (x == 0)//
        //출력 형태 : "Kakao 은행의 계좌 020202(계좌번호)에 3000원이 입금되었습니다."
        cout << account->getBankName() << " 은행의 계좌 " << account->getAccountNum() << "에 " << totalAmount << "원이 입금되었습니다." << endl;
    else
        //출력 형태 : "3000 won has been deposited into the account 020202 of Kakao Bank."
        cout << totalAmount << "won has been deposited into the account " << account->getAccountNum() << " of " << account->getBankName() << " Bank." << endl;

    // 현재 잔액을 출력합니다.
    if (x == 0)
        //출력 형태 : "현재 잔액 : 3000 원"
        cout << "현재 잔액 : ";
    else
        //출력 형태 : "Current Available Cash : 3000 won"
        cout << "Current Available Cash : ";
    cout << account->getBalance();

    if (x == 0) cout << " 원" << endl;
    else cout << " won" << endl;

    cout << "\n";
};

// 3. 출금해주는 함수
void Session::Withdrawal(const map<int, int>& amount, int x) {

    map<int, int>amount2;
    amount2[1000] = 0;
    amount2[5000] = 0;
    amount2[10000] = 0;
    amount2[50000] = 0;
    
    unsigned long long fee = 1000;
    if (!primarySignal) fee = 2000;

    //withdraw할 총량을 계산함
    unsigned long long totalAmount = 0;
    for (const auto& pair: amount) {
        totalAmount += pair.first * pair.second;
    }
    /*
    unsigned long long totalAmount = 0;
    for (auto iter = amount.begin(); iter != amount.end(); iter++) {

        int denomination = iter->first;
        int count = iter->second;

        if (count > 0){
            amount2[iter->first] = iter->second;
        }
        totalAmount += (denomination * count);
    }*/

    map<int, int> totalCash = this->atm->GetAvailableCash();
    int totalAmountCash=0;
    int a[] = { 1000, 5000, 10000, 50000 };

    for (int i = 0; i < 4; i++) {

        if (amount2[a[i]] > totalCash[a[i]]){
            totalAmount += 10000000000000000000;
        }
     }
    
    
    for (auto iter = totalCash.begin(); iter != totalCash.end(); iter++) {


        int denomination2 = iter->first;
        int count2 = iter->second;
        totalAmountCash += (denomination2 * count2);

    }

    //비교해 출금
    if (totalAmountCash < totalAmount) {
        if (x == 0) cout << " 현재 기기 내 현금이 부족합니다\n" << endl;
        else cout << " OUR ATM DOESN'T HAVE ENOUGH MONEY\n" << endl;
    }
    else if (totalAmount + fee > account->getBalance()) {
        if (x == 0) cout << "잔액 부족\n" << endl;
        else cout << " YOU DON'T HAVE ENOUGH MONEY\n" << endl;
    }
    else {
        // 출금금액과 수수료를 ATM과 계좌에서 각각 차감
        atm->SetAvailableCash(amount2, false);  // 가능한 돈을 차감하는 함수로 가정
        account->withdraw(totalAmount + fee);

        int transactionID = GetNextTransactionID();
        account->deposit(totalAmount - fee);


        //History를 저장합니다.
        //형식 : [1] Transaction ID: 1234, Card number: 234, Transaction type: Cash deposit, Amount: 2347, Deposit account number: 23478
        string out = "[";
        out += to_string(atm->GetHistory().size());
        out += "] Transaction ID: ";
        out += to_string(this->currentTransactionID);
        out += ", Card number: ";
        out += account->getMyCard()->getCardNumber();
        out += ", Transaction type: Withdrawal, Amount: ";
        out += to_string(totalAmount);
        out += ", Deposit account number: ";
        out += account->getAccountNum();

        atm->SetHistory(out);
        this->transctionHistoryOfSession.push_back(out);

        //Transaction withdrawTransaction(transactionID, card->getCardNumber(), "Withdraw", totalAmount);
        //transctionHistoryOfSession.push_back(withdrawTransaction);
        //------------------


         // 거래 정보를 출력합니다.
        if (x == 0)//
            //출력 형태 : "Kakao 은행의 계좌 020202(계좌번호)에서 3000원이 출금되었습니다."
            cout << account->getBankName() << " 은행의 계좌 " << account->getAccountNum() << "에서 " << totalAmount << "원이 출금되었습니다." << endl;
        else
            //출력 형태 : "3000 won has been withdrawn from the account 020202 of Kakao Bank."
            cout << totalAmount << "won has been withdrawn from the account " << account->getAccountNum() << " of " << account->getBankName() << " Bank." << endl;

        // 현재 잔액을 출력합니다.
        if (x == 0)
            //출력 형태 : "현재 잔액 : 3000 원"
            cout << "현재 잔액 : ";
        else
            //출력 형태 : "Current Available Cash : 3000 won"
            cout << "Current Available Cash : ";
        cout << account->getBalance();

        if (x == 0) cout << " 원" << endl;
        else cout << " won" << endl;

        cout << "\n";
        //-----------------


        withdrawalCount++;  // 세션 종료 !! 변수가 있음 ATM에서 가져가면 될듯 ??question) ATM에서 어떤걸 하면 되나요??
    }
}



// 4. 현금 송금하는 함수
void Session::CashTransfer(map<int, int> amount, Account* destination, int x) { //destination는 이체하고 자 하는 계좌.

    unsigned long long fee = 5000;

    // ATM에게 현금을 추가합니다.
    atm->SetAvailableCash(amount, true);


    // 수수료 빼고 계좌에 입금
    unsigned long long totalAmount;
    for (const auto& entry : amount) {
        int denomination = entry.first;
        int count = entry.second;
        totalAmount = (denomination * count);
    }

    unsigned long long totaltotalAmount = totalAmount - fee;
    destination->deposit(totaltotalAmount);

    int transactionID = GetNextTransactionID();

    //History를 저장합니다.
    //형식 : [1] Transaction ID: 1234, Card number: 234, Transaction type: Cash deposit, Amount: 2347, Deposit account number: 23478
    string out = "[";
    out += to_string(atm->GetHistory().size());
    out += "] Transaction ID: ";
    out += to_string(this->currentTransactionID);
    out += ", Card number: ";
    out += account->getMyCard()->getCardNumber();
    out += ", Transaction type: Cash transfer, Amount: ";
    out += to_string(totalAmount);
    out += ", account number for withdrawal: ";
    out += account->getAccountNum();
    out += ", account number for deposit: ";
    out += destination->getAccountNum();

    atm->SetHistory(out);
    this->transctionHistoryOfSession.push_back(out);

    //Transaction CashTransferTransaction(transactionID, card->getCardNumber(), "CashTransfer", totaltotalAmount) ;
    //transctionHistoryOfSession.push_back(CashTransferTransaction);
    //------------------

    // 거래 정보를 출력합니다.
    if (x == 0)//
        //출력 형태 : "Kakao 은행의 계좌 020202(계좌번호)로 3000원이 송금되었습니다."
        cout << destination->getBankName() << " 은행의 계좌 " << destination->getAccountNum() << "로 " << totalAmount << "원이 송금되었습니다." << endl;
    else
        //출력 형태 : "3000 won has been transferred to the account 020202 of Kakao Bank."
        cout << totalAmount << "won has been transferred to the account " << destination->getAccountNum() << " of " << destination->getBankName() << " Bank." << endl;
    //-----------------
}


//5. 계좌 송금하는 함수
//수정이 많이 필요합니다.
//계좌 포인터 건드는 법을 모르겠어요 ㅠ
void Session::AccountTransfer(unsigned long long amount, Account* destination, int x) {

    // 이체 수수료(fee)를 초기화합니다.
    unsigned long long fee;

    // 송금 계좌와 수취 계좌의 은행 이름을 가져옵니다.
    string accountName = account->getBankName();
    string destName = destination->getBankName();

    // 은행이 같고, 현재 세션이 주거래 은행인 경우 수수료는 2000원,
    // 은행이 같고, 현재 세션이 타은행 거래 가능인 경우 수수료는 3000원,
    // 은행이 다른 경우 수수료는 4000원으로 설정합니다.
    if ((accountName.compare(destName) == 0) && (primarySignal == true))
        fee = 2000;
    else if ((accountName.compare(destName) == 0) && (primarySignal == false))
        fee = 3000;
    else
        fee = 4000;

    // 잔액이 충분하지 않으면 메시지 출력 후 종료합니다.
    if (amount + fee > account->getBalance()) {
        if (x == 0)
            cout << "잔액 부족\n" << endl;
        else
            cout << "YOU DON'T HAVE ENOUGH MONEY\n" << endl;
    }
    else {
        // 송금 계좌에서 송금액과 수수료를 차감합니다.
        account->withdraw(amount + fee);

        // 수취 계좌에 송금액을 추가합니다.
        destination->deposit(amount);

        //History를 저장합니다.
        //형식 : [1] Transaction ID: 1234, Card number: 234, Transaction type: Cash deposit, Amount: 2347, Deposit account number: 23478
        string out = "[";
        out += to_string(atm->GetHistory().size());
        out += "] Transaction ID: ";
        out += to_string(this->currentTransactionID);
        out += ", Card number: ";
        out += account->getMyCard()->getCardNumber();
        out += ", Transaction type: Account transfer, Amount: ";
        out += to_string(amount);
        out += ", account number for withdrawal: ";
        out += account->getAccountNum();
        out += ", account number for deposit: ";
        out += destination->getAccountNum();

        atm->SetHistory(out);
        this->transctionHistoryOfSession.push_back(out);

        //AccountTransferTransaction newTransaction(destination, account, amount, accountNum, destNum);
        //destination->addTransaction(&newTransaction);

        //transactionHistoryOfSession.push_back(newTransaction);
        //------------------

        // 거래 정보를 출력합니다.
        if (x == 0) {//
            //출력 형태 : "Kakao 은행의 계좌 020202(계좌번호)에서 Kakao 은행의 계좌 020202(계좌번호)로 3000원이 송금되었습니다."
            cout << account->getBankName() << " 은행의 계좌 " << account->getAccountNum() << "에서 " << destination->getBankName() << " 은행의 계좌 " << destination->getAccountNum() << "로 " << amount << "원이 송금되었습니다." << endl;
        }
        else {
            //출력 형태 : "3000 won has been transferred from the account 020202 of Kakao Bank to the account 020202 of Kakao Bank."
            cout << amount << "won has been transferred from the account " << account->getAccountNum() << " of " << account->getBankName() << " Bank to the account " << destination->getAccountNum() << " of " << destination->getBankName() << " Bank." << endl;

            // 현재 잔액을 출력합니다.
            if (x == 0) {
                //출력 형태 : "현재 잔액 : 3000 원"
                cout << "현재 잔액 : ";
            }
            else {
                //출력 형태 : "Current Available Cash : 3000 won"
                cout << "Current Available Cash : ";
                cout << account->getBalance();

                if (x == 0) { cout << " 원" << endl; }
                else { cout << " won" << endl; }
            }
            cout << "\n";
            //-----------------
        }
    }
}


// -------------child of Session class ---------------
class KoreanSession : public Session {
public:
    KoreanSession(ATM* iatm);
    void mainKoreanDisplay();
    void VerifyAccountNum();
    void AuthorizePassword();
};

//------------methods of KoreanSession---------------
void KoreanSession::mainKoreanDisplay() {
    string tmp;
    for (const auto& pair : atm->GetPrimaryBank()) { tmp = pair.first; }
    cout << tmp << " 은행" << endl;
    if (atm->IsMultiBank()) {
        cout << "타은행 거래 가능>" << endl;
    }
    else { cout << "<주거래 은행 전용>" << endl; }
}

void KoreanSession::VerifyAccountNum() {
    string inputAccount;
    bool verified;

    //계좌번호 입력받기
    while (true) {
        cout << " 계좌 번호를 입력해주세요\n" << endl;
        cout << "계좌 번호 : ";
        cin >> inputAccount;
        if (cin.fail() == true) { // 사용자의 입력이 string이 아닌 경우
            cout << "유효하지 않은 문자열입니다." << endl;
            cin.clear();
            cin.ignore(100, '\n');
            continue; //for문 다시 돌아가서 선택하게 하기.
        }
        else if (inputAccount == "x") {
            this->myGlobal->Display();
            continue;
        }

        bool isValid = false;
        for (const auto& accMap : this->myGlobal->getAccountMap()) {
            if (accMap.first == inputAccount) { isValid = true; }
        }
        if (isValid) {
            map<string, Account*>accMap = this->myGlobal->getAccountMap();
            string tempbank = accMap[inputAccount]->getBankName();

            Bank* tmp = nullptr;
            for (const auto& pair : atm->GetPrimaryBank()) { tmp = pair.second; }
            string checkbank = tmp->getBankName();

            if (checkbank.compare(tempbank) == 0) { //현재 세션에서 사용 중인 ATM 객체(atm)의 기본 은행 정보와, 입력된 계좌 번호에 해당하는 Bank 객체의 은행 이름을 비교 ! 두 은행 이름이 같다면, 현재 세션에서 사용 중인 은행이라는 것을 의미
                this->account = accMap[inputAccount]; //같다면, 해당 은행에서 입력된 계좌 번호에 해당하는 Account 객체를 찾아서 account 포인터에 저장합니다. 이렇게 하면 현재 세션에서 사용할 수 있는 계좌를 설정
                this->validAccount = true;
                break;
            }
            else {
                if (atm->IsMultiBank() == 0) { //타은행 계좌를 사용할 수 없다면
                    mainKoreanDisplay();
                    cout << "타은행 계좌는 사용하실 수 없습니다\n" << endl;
                    this->validAccount = false;
                }
                else {
                    primarySignal = false;
                    this->account = accMap[inputAccount];
                }
            }

        }
        else {
            mainKoreanDisplay();
            cout << "입력한 계좌번호가 존재하지 않습니다." << endl;
            this->validAccount = false;
        }

    }
}

//확인되면 authorizationSignal을 true로 변경하는 함수
void KoreanSession::AuthorizePassword() {
    for (int i = 1; i < 4; i++) { // 비밀번호 3번까지 입력 가능 !
        string inputPassword;
        mainKoreanDisplay();
        cout << "비밀번호를 입력해주세요" << endl;
        cout << "비밀번호 : ";
        cin >> inputPassword;
        if (cin.fail() == true) { // 사용자의 입력이 string이 아닌 경우
            cout << "유효하지 않은 문자열입니다." << endl;
            cin.clear();
            cin.ignore(100, '\n');
            continue; //for문 다시 돌아가서 선택하게 하기.
        }
        else if (inputPassword == "x") {
            this->myGlobal->Display();
            continue;
        }
        if (Authorization(inputPassword)) {
            authorizationSignal = true;
            break;
        }
        else {
            authorizationSignal = false;
            authorizationCount++;
            mainKoreanDisplay();
            cout << "비밀번호를 " << authorizationCount << "회 틀렸습니다\n" << endl;
        }
    }
    if (authorizationSignal == false) {
        mainKoreanDisplay();
        cout << " 비밀번호 입력을 3회 실패하여 세션이 종료됩니다" << endl;
    }
};



KoreanSession::KoreanSession(ATM* iatm) {
    //Session Protected parameter 초기화 - account, card, transactionHistoryOfSession, currentTransactionID, myGlobal 비어있음
    atm = iatm;
    this->SetmyGlobal(this->atm->GetMyGlobal());
    primarySignal = true; //
    authorizationCount = 0; //
    withdrawalCount = 0; // 이거 처리 !
    authorizationSignal = true;


    mainKoreanDisplay();

    //계좌번호 입력받고 존재하는지 확인, 유효하면 account에 저장되고 아니면 validAccount=false
    VerifyAccountNum();

    if (validAccount) { // 유효한 계좌인 경우 (비밀번호 인증 로직)
        AuthorizePassword();//확인되면 authorizationSignal을 true로 변경하는 함수
        if (authorizationSignal) {
            bool sessionExitSignal = true;
            while (sessionExitSignal) {
                mainKoreanDisplay();

                //서비스 선택 UI
                cout << "원하시는 서비스를 선택해주세요\n" << endl;
                cout << "1. 입금    2. 출금   3. 송금   4. 서비스 종료\n" << endl; //거래 3번 이상 시 세션 새로 열기
                cout << "번호 입력 : ";
                int transactionNum = -1;
                cin >> transactionNum;

                if (cin.fail() == true) { // 사용자의 입력이 숫자가 아닌 경우
                    cout << "유효하지 않은 번호입니다." << endl;
                    cin.clear();
                    cin.ignore(100, '\n');
                    continue; //for문 다시 돌아가서 선택하게 하기.
                }
                else if (transactionNum == 0000000000) {
                    this->myGlobal->Display();
                    continue;
                }
                else if (transactionNum == 5) {
                    // 사용자가 종료를 선택했을 때 루프를 종료
                    break;
                }

                if (transactionNum == 1) { // 입금 (1000월 , 5000원 , 10000원, 50000원을 받아야함. )
                    //입금 UI------------------
                    mainKoreanDisplay();
                    cout << " 입금 서비스 입니다. " << endl;
                    cout << " 1. 현금 입금     2. 수표 입금" << endl;
                    cout << "번호 입력 : ";
                    int depositinput = -1;
                    cin >> depositinput;

                    //input 체크
                    if (cin.fail() == true) {
                        cout << "유효하지 않은 번호입니다. 다시 입력해주세요." << endl;
                        cin.clear();
                        cin.ignore(100, '\n');
                        continue;
                    };
                    if (depositinput == 0000000000) {
                        this->myGlobal->Display();
                        continue;
                    };


                    //선택 : 현금 입금
                    map<int, int> billCounts; // 각 지폐의 갯수를 저장할 맵
                    billCounts[1000] = 0;
                    billCounts[5000] = 0;
                    billCounts[10000] = 0;
                    billCounts[50000] = 0;
                    
                    if (depositinput == 1) {
                        while (true) {
                            mainKoreanDisplay();
                            //map<int, int> billCounts; // 각 지폐의 갯수를 저장할 맵
                            cout << "입금하실 지폐의 종류를 선택해주세요\n" << endl;
                            cout << "1. 1000원  2. 5000원  3. 10000원  4. 50000원 5. 종료" << endl;
                            int sel = -1;
                            cin >> sel;
                            if (cin.fail() == true || sel < 1 || sel > 5) {
                                cout << "유효하지 않은 번호입니다." << endl;
                                cin.clear();
                                cin.ignore(100, '\n');
                                continue;
                            }
                            else if (sel == 0000000000) {
                                this->myGlobal->Display();
                                continue;
                            }



                            if (sel == 5) {
                                // 사용자가 종료를 선택했을 때 루프를 종료
                                break;
                            }

                            int Type;
                            if (sel == 1) {
                                Type = 1000;
                            }
                            else if (sel == 2) {
                                Type = 5000;

                            }
                            else if (sel == 3) {
                                Type = 10000;

                            }
                            else if (sel == 4) {
                                Type = 50000;
                            }

                            cout << "입금하실 지폐의 장 수를 입력해주세요: ";
                            int bill = -1;
                            cin >> bill;

                            //input 체크
                            if (cin.fail() == true) {
                                cout << "유효하지 않은 번호입니다. 다시 입력해주세요." << endl;
                                cin.clear();
                                cin.ignore(100, '\n');
                                continue;
                            }
                            else if (depositinput == 0000000000) {
                                this->myGlobal->Display();
                                continue;
                            }


                            billCounts[Type] = bill;
                            CashDeposit(billCounts, 0);


                            /* ??
                             //input 체크 완료
                             map<int, int> cashinput;
                             cashinput.insert({})
                             CashDeposit(map<int, int> amount, int x)
                             ---------------------

                             */

                        }
                    }
                    else if (depositinput == 2) {
                        // 수표 입금 처리
                        int numIterations = 0;

                        while (true) {
                            if (numIterations == 30) {
                                cout << "수표는 30장 까지 입금이 가능합니다. " << endl;
                                break;
                            }
                            else {
                                cout << "1. 수표입력 2. 종료 \n" << endl;
                                int chice = -1;
                                cin >> chice;
                                if (cin.fail() == true) {
                                    cout << "유효하지 않은 번호입니다. 다시 입력해주세요." << endl;
                                    cin.clear();
                                    cin.ignore(100, '\n');
                                    continue;
                                }
                                else if (chice == 0000000000) {
                                    this->myGlobal->Display();
                                    continue;
                                }
                                if (chice == 2) {
                                    break;
                                }
                                else {
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
                                    else if (numBill == 0000000000) {
                                        this->myGlobal->Display();
                                        continue;
                                    }
                                    CheckDeposit(numBill, 0);
                                    numIterations++;
                                }
                            }
                        }

                    }
                    else { // "1. 현금 입금     2. 수표 입금"에서 1과 2나 0000000000이 아닌 input이 들어오는 경우
                        cout << "유효하지 않은 번호입니다." << endl;
                    }






                }
                else if (transactionNum == 2) {// 출금
                 //세션이 닫치게 만들어야함 !!!!!!!!!

                    if (withdrawalCount == 3) {
                        cout << "       세션 1회 당 출금 가능한 액수를 초과하셨습니다\n" << endl;
                    }

                    else {
                        while (true) {
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
                            }
                            else if (bill == 0000000000) {
                                this->myGlobal->Display();
                                continue;
                            }

                            if (bill == 5) {
                                // 사용자가 종료를 선택했을 때 루프를 종료
                                break;
                            }

                            int billType;
                            if (bill == 1) {

                                billType = 1000;

                            }
                            else if (bill == 2) {
                                billType = 5000;

                            }
                            else if (bill == 3) {
                                billType = 10000;

                            }
                            else if (bill == 4) {
                                billType = 50000;

                            }

                            cout << "출금하실 지폐의 장 수를 입력해주세요: ";
                            int numBill = -1;

                            cin >> numBill;
                            if (cin.fail() == true || numBill <= 0) {
                                cout << "유효하지 않은 번호입니다." << endl;
                                cin.clear();
                                cin.ignore(100, '\n');
                                continue;

                            }
                            else if (numBill == 0000000000) {
                                this->myGlobal->Display();
                                continue;
                            }


                            billCounts[billType] = numBill;
                            // 한 번에 거래 가능한 장 수
                            if (numBill > 50) {
                                cout << "거래 1회 당 출출금 가능한 장 수를 초과하셨습니다." << endl;
                                break;

                            }
                            Withdrawal(billCounts, 0);
                        }
                    }
                }
                else if (transactionNum == 3) { // 송금
                    unsigned long long inAmount;
                    int transferNum = -1;
                    while (true) {
                        cout << "송금 서비스 입니다\n" << endl;
                        cout << "             1. 계좌 송금 (계좌 -> 계좌)" << endl;
                        cout << "             2. 현금 송금 (현금 -> 계좌)\n" << endl;
                        cout << "==================================================" << endl;
                        cout << "번호 입력 : ";
                        cin >> transferNum;
                        if (cin.fail() == true) {
                            cout << "유효하지 않은 번호입니다." << endl;
                            cin.clear();
                            cin.ignore(100, '\n');
                            continue;
                        }
                        else if (transferNum == 0000000000) {
                            this->myGlobal->Display();
                            continue;
                        }
                        else { break; };
                    }
                    if (transferNum == 1) { // Account Transfer
                        while (true) {
                            cout << "계좌 송금 서비스를 선택하셨습니다\n" << endl;
                            cout << "송금하실 금액을 입력해주십시오\n" << endl;
                            cout << "송금 금액 : ";
                            inAmount = -1;
                            cin >> inAmount;
                            if (cin.fail() == true) {
                                cout << "유효하지 않은 번호입니다." << endl;
                                cin.clear();
                                cin.ignore(100, '\n');
                                continue;
                            }
                            else if (inAmount == 0000000000) {
                                this->myGlobal->Display();
                                continue;
                            }
                            else if (inAmount < 0) {
                                cout << "유효하지 않은 번호입니다." << endl;
                            }
                            else if (inAmount == 0) {
                                cout << "0 원을 송금할 수는 없습니다\n" << endl;
                            }
                            else { break; };
                        }
                        mainKoreanDisplay();

                        bool keepgoing = true;
                        while (keepgoing) {
                            cout << "          받으실 분의 계좌 번호를 입력해주십시오\n" << endl;
                            cout << "받으실 분 계좌 번호 : ";
                            string inDest;
                            cin >> inDest;


                            if (cin.fail() == true) {
                                cout << "유효하지 않은 번호입니다." << endl;
                                cin.clear();
                                cin.ignore(100, '\n');
                                continue;

                            }
                            else if (inDest == "x") {
                                this->myGlobal->Display();
                                continue;
                            }
                            else {
                                //Global에서 account map 가져와서 destination account* 넘겨주기
                                bool isAccNotExist = true;
                                for (const auto& pair : this->myGlobal->getAccountMap()) {
                                    Account* accTmp = pair.second;
                                    if (pair.first == inDest) {
                                        AccountTransfer(inAmount, accTmp, 0);
                                        isAccNotExist = false;
                                        keepgoing = false;
                                    }
                                }
                                if (isAccNotExist) {
                                    cout << "입력한 계좌번호가 존재하지 않습니다. 다시 입력해주세요." << endl;
                                    continue;
                                }
                                /*
                                auto it = this->myGlobal->getAccountMap().find(inDest);

                                if (it != this->myGlobal->getAccountMap().end()) {
                                    AccountTransfer(inAmount, it->second, 0);

                                }
                                else {
                                    // 계좌가 존재하지 않는 경우
                                    cout << "입력한 계좌번호가 존재하지 않습니다. 다시 입력해주세요." << endl;
                                    continue;
                                }
                                */
                            }
                        }

                    }

                    /*
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
                     */
                    
                    }
                    if (transactionNum == 4) { // 서비스 종료

                        sessionExitSignal = false;
                    }




                
                //}




                cout << "세션 종료" << endl;
                cout << "ATM을 이용해주셔서 감사합니다\n" << endl;
                if (GetSessionHistory().size() == 0) {  //히스토리 부분
                    cout << "해당 세션에는 거래 내역이 없습니다\n" << endl;
                }
                else {
                    cout << "해당 세션 내 총 거래 내역" << endl;

                    //atm->addTransaction(GetSessionHistory()); //ATM에 넘겨주기.

                    for (int i = 0; i < GetSessionHistory().size(); i++) {
                        cout << GetSessionHistory()[i] << endl; // 내역 출력
                    }

                }
            }
        }

    }
    else { cout << " 세션이 종료됩니다. " << endl; }
}//class 끝

//------------ - childs of Session - EnglishSession--------------
class EnglishSession : public Session {
public:
    EnglishSession(ATM* iatm);
    void mainEnglishDisplay();
    void VerifyAccountNum();
    void AuthorizePassword();
};

// ------------methods of EnglishSession---------------
void EnglishSession::mainEnglishDisplay() {
    string tmp;
    for (const auto& pair : atm->GetPrimaryBank()) { tmp = pair.first; }
    cout << tmp << " Bank" << endl;
    if (atm->IsMultiBank()) {
        cout << "Available for transactions in other banks>" << endl;
    }
    else { cout << "<Primary Bank Only>" << endl; }
}

void EnglishSession::VerifyAccountNum() {
    string inputAccount;
    bool verified;

    //계좌번호 입력받기
    while (true) {
        cout << " Please enter the account number\n" << endl;
        cout << "Account Number: ";
        cin >> inputAccount;
        if (cin.fail() == true) { // 사용자의 입력이 string이 아닌 경우
            cout << "Invalid string." << endl;
            cin.clear();
            cin.ignore(100, '\n');
            continue; //for문 다시 돌아가서 선택하게 하기.
        }
        else if (inputAccount == "x") {
            this->myGlobal->Display();
            continue;
        }

        bool isValid = false;
        for (const auto& accMap : this->myGlobal->getAccountMap()) {
            if (accMap.first == inputAccount) { isValid = true; }
        }
        if (isValid) {
            map<string, Account*>accMap = this->myGlobal->getAccountMap();
            string tempbank = accMap[inputAccount]->getBankName();

            Bank* tmp = nullptr;
            for (const auto& pair : atm->GetPrimaryBank()) { tmp = pair.second; }
            string checkbank = tmp->getBankName();

            if (checkbank.compare(tempbank) == 0) { //현재 세션에서 사용 중인 ATM 객체(atm)의 기본 은행 정보와, 입력된 계좌 번호에 해당하는 Bank 객체의 은행 이름을 비교 ! 두 은행 이름이 같다면, 현재 세션에서 사용 중인 은행이라는 것을 의미
                this->account = accMap[inputAccount]; //같다면, 해당 은행에서 입력된 계좌 번호에 해당하는 Account 객체를 찾아서 account 포인터에 저장합니다. 이렇게 하면 현재 세션에서 사용할 수 있는 계좌를 설정
                this->validAccount = true;
                break;
            }
            else {
                if (atm->IsMultiBank() == 0) { //타은행 계좌를 사용할 수 없다면
                    mainEnglishDisplay();
                    cout << "Cannot use accounts from other banks\n\n" << endl;
                    this->validAccount = false;
                }
                else {
                    primarySignal = false;
                    this->account = accMap[inputAccount];
                }
            }

        }
        else {
            mainEnglishDisplay();
            cout << "The entered account number does not exist." << endl;
            this->validAccount = false;
        }

    }
}


void EnglishSession::AuthorizePassword() {
    for (int i = 1; i < 4; i++) {
        string inputPassword;
        mainEnglishDisplay();
        cout << "Please enter the password" << endl;
        cout << "Password: ";
        cin >> inputPassword;
        if (cin.fail() == true) {
            cout << "Invalid string." << endl;
            cin.clear();
            cin.ignore(100, '\n');
            continue;
        }
        else if (inputPassword == "x") {
            this->myGlobal->Display();
            continue;
        }
        if (Authorization(inputPassword)) {
            authorizationSignal = true;
            break;
        }
        else {
            authorizationSignal = false;
            authorizationCount++;
            mainEnglishDisplay();
            cout << "Incorrect password attempt " << authorizationCount << " time(s)\n" << endl;
        }
    }
    if (authorizationSignal == false) {
        mainEnglishDisplay();
        cout << "Failed to enter the password 3 times. The session will be terminated." << endl;
    }
};

EnglishSession::EnglishSession(ATM* iatm) {
    atm = iatm;
    this->SetmyGlobal(this->atm->GetMyGlobal());
    primarySignal = true;
    authorizationCount = 0;
    withdrawalCount = 0;
    authorizationSignal = true;

    mainEnglishDisplay();

    VerifyAccountNum();

    if (validAccount) {
        AuthorizePassword();
        if (authorizationSignal) {
            bool sessionExitSignal = true;
            while (sessionExitSignal) {
                mainEnglishDisplay();

                cout << "Please select the desired service\n" << endl;
                cout << "1. Deposit    2. Withdrawal   3. Transfer   4. Exit\n" << endl;
                cout << "Enter the number: ";
                int transactionNum = -1;
                cin >> transactionNum;

                if (cin.fail() == true) {
                    cout << "Invalid number." << endl;
                    cin.clear();
                    cin.ignore(100, '\n');
                    continue;
                }
                else if (transactionNum == 0000000000) {
                    this->myGlobal->Display();
                    continue;
                }
                else if (transactionNum == 5) {
                    break;
                }

                if (transactionNum == 1) {
                    mainEnglishDisplay();
                    cout << "Deposit service" << endl;
                    cout << " 1. Cash Deposit     2. Check Deposit" << endl;
                    cout << "Enter the number: ";
                    int depositinput = -1;
                    cin >> depositinput;

                    if (cin.fail() == true) {
                        cout << "Invalid number. Please enter again." << endl;
                        cin.clear();
                        cin.ignore(100, '\n');
                        continue;
                    };
                    if (depositinput == 0000000000) {
                        this->myGlobal->Display();
                        continue;
                    };



                    if (depositinput == 1) {
                        while (true) {
                            mainEnglishDisplay();
                            cout << "Please select the denomination of the deposited bill\n" << endl;
                            cout << "1. 1000 won  2. 5000 won  3. 10000 won  4. 50000 won 5. Exit" << endl;
                            int sel = -1;
                            cin >> sel;

                            map<int, int> billCounts;
                            billCounts[1000] = 0;
                            billCounts[5000] = 0;
                            billCounts[10000] = 0;
                            billCounts[50000] = 0;

                            if (sel == 0000000000) {
                                this->myGlobal->Display();
                                continue;
                            }
                            else if (cin.fail() == true || sel < 1 || sel > 5) {
                                cout << "Invalid number." << endl;
                                cin.clear();
                                cin.ignore(100, '\n');
                                continue;
                            }

                            if (sel == 5) {
                                break;
                            }

                            int Type;
                            if (sel == 1) {
                                Type = 1000;
                            }
                            else if (sel == 2) {
                                Type = 5000;
                            }
                            else if (sel == 3) {
                                Type = 10000;
                            }
                            else if (sel == 4) {
                                Type = 50000;
                            }

                            cout << "Please enter the number of bills to deposit: ";
                            int bill = -1;
                            cin >> bill;

                            if (cin.fail() == true) {
                                cout << "Invalid number. Please enter again." << endl;
                                cin.clear();
                                cin.ignore(100, '\n');
                                continue;
                            }
                            else if (depositinput == 0000000000) {
                                this->myGlobal->Display();
                                continue;
                            }

                            billCounts[Type] = bill;
                            CashDeposit(billCounts, 1);
                        }
                    }
                    else if (depositinput == 2) {
                        int numIterations = 0;
                        while (true) {
                            if (numIterations == 30) {
                                cout << "You can deposit up to 30 checks." << endl;
                                break;
                            }
                            else {
                                cout << "1. Enter check 2. Exit\n" << endl;
                                int choice = -1;
                                cin >> choice;
                                if (cin.fail() == true) {
                                    cout << "Invalid number. Please enter again." << endl;
                                    cin.clear();
                                    cin.ignore(100, '\n');
                                    continue;
                                }
                                else if (choice == 0000000000) {
                                    this->myGlobal->Display();
                                    continue;
                                }
                                if (choice == 2) {
                                    break;
                                }
                                else {
                                    cout << "Enter the check amount: ";
                                    cout << "Check : ";
                                    int numBill = -1;
                                    cin >> numBill;

                                    if (cin.fail() == true) {
                                        cout << "Invalid number." << endl;
                                        cin.clear();
                                        cin.ignore(100, '\n');
                                        continue;
                                    }
                                    else if (numBill == 0000000000) {
                                        this->myGlobal->Display();
                                        continue;
                                    }
                                    CheckDeposit(numBill, 1);
                                    numIterations++;
                                }
                            }
                        }
                        continue;
                    }
                    else {
                        cout << "Invalid number." << endl;
                    }


                }
                else if (transactionNum == 2) { // Withdrawal
                    if (withdrawalCount == 3) {
                        cout << "You have exceeded the maximum withdrawal limit per session.\n" << endl;
                    }
                    else {
                        while (true) {
                            mainEnglishDisplay();
                            map<int, int> billCounts; // Map to store the count of each bill
                            cout << "Select the type of bill to withdraw\n" << endl;
                            cout << "1. 1000 won  2. 5000 won  3. 10000 won  4. 50000 won  5. Exit" << endl;
                            cout << "Enter number: ";
                            int bill = -1;
                            cin >> bill;

                            if (bill == 0000000000) {
                                this->myGlobal->Display();
                                continue;
                            }
                            else if (cin.fail() == true || bill < 1 || bill > 5) {
                                cout << "Invalid number." << endl;
                                cin.clear();
                                cin.ignore(100, '\n');
                                continue;
                            }

                            if (bill == 5) {
                                // Exit the loop when the user chooses to exit
                                break;
                            }

                            int billType;
                            if (bill == 1) {
                                billType = 1000;
                            }
                            else if (bill == 2) {
                                billType = 5000;
                            }
                            else if (bill == 3) {
                                billType = 10000;
                            }
                            else if (bill == 4) {
                                billType = 50000;
                            }

                            cout << "Enter the number of bills to withdraw: ";
                            int numBill = -1;

                            cin >> numBill;
                            if (cin.fail() == true || numBill <= 0) {
                                cout << "Invalid number." << endl;
                                cin.clear();
                                cin.ignore(100, '\n');
                                continue;
                            }
                            else if (numBill == 0000000000) {
                                this->myGlobal->Display();
                                continue;
                            }

                            billCounts[billType] = numBill;
                            // Limit the number of bills that can be processed at once
                            if (numBill > 50) {
                                cout << "You have exceeded the maximum number of bills that can be processed in one transaction." << endl;
                                break;
                            }
                            Withdrawal(billCounts, 1);
                        }
                    }
                }
                else if (transactionNum == 3) { // Transfer
                    unsigned long long inAmount;
                    int transferNum = -1;
                    while (true) {
                        cout << "Transfer service\n" << endl;
                        cout << "             1. Account Transfer (Account to Account)" << endl;
                        cout << "             2. Cash Transfer (Cash to Account)\n" << endl;
                        cout << "==================================================" << endl;
                        cout << "Enter number: ";
                        cin >> transferNum;
                        if (cin.fail() == true) {
                            cout << "Invalid number." << endl;
                            cin.clear();
                            cin.ignore(100, '\n');
                            continue;
                        }
                        else if (transferNum == 0000000000) {
                            this->myGlobal->Display();
                            continue;
                        }
                        else {
                            break;
                        };
                    }
                    if (transferNum == 1) { // Account Transfer
                        while (true) {
                            cout << "You have selected the Account Transfer service\n" << endl;
                            cout << "Enter the amount to transfer\n" << endl;
                            cout << "Transfer amount: ";
                            inAmount = -1;
                            cin >> inAmount;
                            if (cin.fail() == true) {
                                cout << "Invalid number." << endl;
                                cin.clear();
                                cin.ignore(100, '\n');
                                continue;
                            }
                            else if (inAmount == 0000000000) {
                                this->myGlobal->Display();
                                continue;
                            }
                            else if (inAmount < 0) {
                                cout << "Invalid number." << endl;
                            }
                            else if (inAmount == 0) {
                                cout << "You cannot transfer 0 won\n" << endl;
                            }
                            else {
                                break;
                            };
                        }
                        mainEnglishDisplay();

                        bool keepgoing = true;
                        while (keepgoing) {
                            cout << "Enter the recipient's account number\n" << endl;
                            cout << "Recipient's account number: ";
                            string inDest;
                            cin >> inDest;

                            if (cin.fail() == true) {
                                cout << "Invalid number." << endl;
                                cin.clear();
                                cin.ignore(100, '\n');
                                continue;
                            }
                            else if (inDest == "x") {
                                this->myGlobal->Display();
                                continue;
                            }
                            else {
                                // Get the account map from Global and pass the destination account*
                                bool isAccNotExist = true;
                                for (const auto& pair : this->myGlobal->getAccountMap()) {
                                    Account* accTmp = pair.second;
                                    if (pair.first == inDest) {
                                        AccountTransfer(inAmount, accTmp, 0);
                                        isAccNotExist = false;
                                        keepgoing = false;
                                    }
                                }
                                if (isAccNotExist) {
                                    cout << "The entered account number does not exist. Please enter again." << endl;
                                    continue;
                                }

                                /*
                                auto it = this->myGlobal->getAccountMap().find(inDest);

                                if (it != this->myGlobal->getAccountMap().end()) {
                                    AccountTransfer(inAmount, it->second, 0);
                                }
                                else {
                                    // If the account does not exist
                                    cout << "The entered account number does not exist. Please enter again." << endl;
                                    continue;
                                }
                                */
                            }
                        }
                    }

                    

                }else if (transactionNum == 4) { // Service Termination
                    sessionExitSignal = false;
                }
            }
                cout << "Session terminated" << endl;
                cout << "Thank you for using the ATM\n" << endl;
                if (GetSessionHistory().size() == 0) {  // History section
                    cout << "There is no transaction history for this session\n" << endl;
                }
                else {
                    cout << "Total transaction history for this session" << endl;

                    // atm->addTransaction(GetSessionHistory()); // Pass to ATM.

                    for (int i = 0; i < GetSessionHistory().size(); i++) {
                        cout << GetSessionHistory()[i] << endl; // Display history
                    }

                }
            }
        }
    }

ATM::ATM() {
    cout << "아무 input 없이 ATM을 생성할 수 없습니다." << endl;
    cout << "primary bank의 pointer, 모든 bank의 map, admin card의 pointer를 넣어 ATM을 생성해주세요." << endl;
    cout << "자동으로 이 ATM을 제거합니다." << endl;
    delete this;

}

ATM::ATM(Bank* pb, map<string, Bank*> allb, string admin) {
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
    cout << "Serial Number : " << endl;

    cin >> this->SerialNumber;
    this->PrimaryBank.insert({ pb->getBankName(), pb });
    allb.erase(bankname);
    this->NonPrimaryBank.insert(allb.begin(), allb.end());
    cout << "Primary 및 Nonprimary bank 설정이 완료되었습니다" << endl;
    this->AdminCard = admin;
    cout << "Admin Card 설정이 완료되었습니다" << endl;
    while (true) {
        cout << "Bilingual ATM입니까?" << endl;
        cout << "숫자로 입력해주세요" << endl;
        cout << "[1]Yes    [2]No" << endl;
        cin >> bi;
        if (cin.fail() == true) {
            cout << "유효하지 않은 번호입니다. 다시 입력해주세요." << endl;
            cin.clear();
            cin.ignore(100, '\n');
            continue;
        }
        else if (bi == 0000000000) {
            this->myGlobal->Display();
            continue;
        }

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
        }
    }

    while (true) {
        cout << "MultiBank ATM입니까?" << endl;
        cout << "숫자로 입력해주세요" << endl;
        cout << "[1]Yes    [2]No" << endl;
        cin >> mul;
        if (cin.fail() == true) {
            cout << "유효하지 않은 번호입니다. 다시 입력해주세요." << endl;
            cin.clear();
            cin.ignore(100, '\n');
            continue;
        }
        else if (mul == 0000000000) {
            this->myGlobal->Display();
            continue;
        }
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

        }
    }
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

int ATM::NumberOfATM = 0;

void ATM::Start() {
    //기본적인 모든 session 열기 전 수행을 하는 함수입니다.

    //기본 선택 : (Card 입력받기)
    int firstsel;
    cout << "Welcome" << endl;
    cout << "To start a session, please insert your debit card" << endl;
    string CN;
    string PW;
    cout << "Insert card number" << endl;
    cin >> CN;
    cout << "Insert password" << endl;
    cin >> PW;
    //Card 입력받은 경우 : admin인지, 올바른 카드인지 확인 후 session 열어주기
    if (CheckAdmin(CN)) {
        int sel = 1;
        bool repeat = true;
        cout << "Welcome Administrator" << endl;
        while (repeat) {
            cout << "[1] Transaction History" << endl;
            cin >> sel;
            if (cin.fail() == true) {
                cout << "유효하지 않은 번호입니다. 다시 입력해주세요." << endl;
                cin.clear();
                cin.ignore(100, '\n');
                continue;
            }
            else if (sel == 0000000000) {
                this->myGlobal->Display();
                continue;
            }

            if (sel == 1) {
                ShowHistory();
                repeat = false;
            }
            else if (sel == 0000000000) {
                this->myGlobal->Display();
                continue;
            }
            else {
                cout << "error : 올바른 input을 입력해주세요" << endl;
            }
        }
    }
    else if (CheckInvalidCard(CN, PW)) {
        OpenSession();
    }
    else { cout << "올바르지 않은 카드입니다." << endl; }


    //Session 종료 또는 invalid card : 카드 return 표시하기

}
bool ATM::CheckInvalidCard(string cardnum, string pw) {
    ///////////////////////////////이 부분 어떻게 할지, bank에서 카드 맵 저장하는게 나을지도
    bool isExist = false;
    for (const auto& banks : GetPrimaryBank()) {
        map<string, Account*> accMap = banks.second->AccountsInBank();
        for (const auto& accs : accMap) {
            cout << accs.second->getAccountNum() << endl;
            if (accs.second->getMyCard()->getCardNumber() == cardnum && accs.second->verifyPW(pw)) {
                isExist = true;
                break;
            };
        }
    }
    for (const auto& banks : GetNonPrimaryBank()) {
        map<string, Account*> accMap = banks.second->AccountsInBank();
        for (const auto& accs : accMap) {
            cout << accs.second->getAccountNum() << endl;
            if (accs.second->getMyCard()->getCardNumber() == cardnum && accs.second->verifyPW(pw)) {
                isExist = true;
                break;
            };
        }
    }
    return isExist;
}

bool ATM::CheckAdmin(string cardnum) {
    bool isAdmin = false;
    if (cardnum == this->AdminCard) {
        isAdmin = true;
    }
    return isAdmin;
}
void ATM::OpenSession() {
    //언어 받고 session열어주기
    if (this->Bilingual) {
        int sel;
        while (true) {
            cout << "Select Language" << endl;
            cout << "[1] English [etc] Korean" << endl;
            cin >> sel;
            if (cin.fail() == true) { // 사용자의 입력이 string이 아닌 경우
                cout << "유효하지 않은 문자열입니다." << endl;
                cin.clear();
                cin.ignore(100, '\n');
                continue; //for문 다시 돌아가서 선택하게 하기.


            }
            else if (sel == 0000000000) {
                this->myGlobal->Display();
                continue;

            }
            else {
                if (sel == 1) {
                    this->CurrentSession = new EnglishSession(this);
                    CurrentSession->SetmyGlobal(this->myGlobal);
                    break;
                }
                else {
                    this->CurrentSession = new KoreanSession(this);
                    CurrentSession->SetmyGlobal(this->myGlobal);
                    break;
                }
            };
        }
    }
    else {
        this->CurrentSession = new EnglishSession(this);
        CurrentSession->SetmyGlobal(this->myGlobal);

    }
}

void ATM::SetAvailableCash(map<int, int> inputcash, bool Plus) {
    if (Plus) {
        for (auto iter = this->AvailableCash.begin(); iter != this->AvailableCash.end(); iter++) {
            int currentnum = inputcash.find(iter->first)->second;
            iter->second += currentnum;
        }
    }
    else {
        for (auto iter = this->AvailableCash.begin(); iter != this->AvailableCash.end(); iter++) {
            int currentnum = inputcash.find(iter->first)->second;
            iter->second -= currentnum;
        }
    }
    int sum = 0;
    for (auto iter = this->AvailableCash.begin(); iter != this->AvailableCash.end(); iter++) {
        sum += ((iter->first) * (iter->second));

        this->AvailableCashAmount = sum;
    }
}

void ATM::ShowHistory() {
    //History -> vector<string>
    //cout은 terminal에 프린트, out은 History.txt에 프린트하는 함수입니다.
    ofstream out("History.txt");
    if (out.is_open()) {
        cout << "----------------------History--------------------" << endl;
        out << "----------------------History--------------------" << endl;
        for (auto iter = this->History.begin(); iter != this->History.end(); iter++) {
            cout << *iter << endl;
            out << *iter << endl;
        }
        cout << "------------------------------------------------" << endl;
        out << "------------------------------------------------" << endl;
    }
    else {
        cout << "Error : history 파일 안열림" << endl;
    }
    out.close();

}
void ATM::ShowAvailableCash() {
    int total = 0;
    cout << " Remaining Cash: ( ";
    for (auto iter = this->AvailableCash.begin(); iter != this->AvailableCash.end(); iter++) {
        cout << iter->first << "원X" << iter->second << "장  ";
        total += iter->first * iter->second;
    }
    cout << ") total : " << total << endl;
}
////////////////////////////////////////change 11.28
///
///

//----------------------------methods of Global----------------------------------------
//-------------------------------------------------------------------------------------
void Global::setAccountMap(map<string, Account*> inmap) {
    this->AccountMap = inmap;
}
void Global::setATMMap(map<string, ATM*> inmap) {
    this->ATMMap = inmap;
}

void Global::Display() {
    //모든 ATM의 정보 출력
    for (pair<string, ATM*> i : ATMMap) {
        cout << "(ATM [SN : " << i.second->GetSerialNum();
        cout << "] remaining cash: " << i.second->GetAvailableCashAmount() << " ) ";
    }

    //모든 Account의 정보 출력
    for (pair<string, Account*> p : AccountMap) {
        cout << "(Account [Bank: " << p.second->getBank()->getBankName() << ", No: " << p.first;
        cout << ", Owner: " << p.second->getOwnerName() << "] balance: " << p.second->getBalance() << " ) ";
    }
}



int main() {

    //Bank 선언
    int NumofBank;
    string InputBankName1;
    map <string, Bank*> InputBankMap;
    cout << "BANK를 선언하겠습니다" << endl;
    cout << "몇개의 은행을 만드시겠습니까?" << endl;
    cin >> NumofBank;
    for (int i = 0; i < NumofBank; i++) {
        string BankName1;
        cout << "은행" << (i + 1) << "의 이름을 입력해주세요" << endl;
        cin >> BankName1;
        InputBankMap.insert({ BankName1,new Bank(BankName1) });
    }

    //Account 선언
    map<string, Account*> AccountMap;
    map<string, Card*> inputCardMap;
    int NumofAccount;
    string pb;
    string AccountNum;
    string pw;
    string ownername;


    cout << "몇개의 admin card를 생성하시겠습니까?" << endl;
    int num = -1;
    cin >> num;
    for (int i = 0; i < num; i++) {
        cout << "관리자 권한을 부여할 admin card 번호를 입력하세요." << endl;
        string cardNumber;
        cin >> cardNumber;
    }

    cout << "Account를 선언하겠습니다" << endl;
    cout << "몇개의 Account를 만드시겠습니까?" << endl;
    cin >> NumofAccount;
    for (int i = 0; i < NumofAccount; i++) {
        cout << "계좌" << (i + 1) << "의 주거래 은행을 알려주세요" << endl;
        cin >> pb;
        cout << "계좌번호를 입력해주세요" << endl;
        cin >> AccountNum;
        cout << "계좌 소유주의 성명을 입력해주세요" << endl;
        cin >> ownername;
        cout << "계좌 비밀번호를 입력해주세요" << endl;
        cin >> pw;
        //const string& accountNum, const string& password, const string& ownerName, Bank* bank
        map<string, Bank*> inputTMP;
        inputTMP[pb] = InputBankMap[pb];
        //Account(AccountNum, pw, ownername, inputTMP); //수정중
        AccountMap.insert({ AccountNum, new Account(AccountNum, pw, ownername, inputTMP[pb]) });//stop
        map<string, Account*> bankin;
        bankin[AccountNum] = AccountMap[AccountNum];
        InputBankMap[pb]->setAccounts(bankin);

        //Card 선언
        //적어도 admin card는 여기에서 선언되어 ATM을 생성할 때 넣어줘야 함.'
        cout << "카드번호를 입력하세요" << endl;
        string cardNumber;
        cin >> cardNumber;
        AccountMap[AccountNum]->setMyCard(new Card(cardNumber, AccountNum));
        inputCardMap.insert({ cardNumber, AccountMap[AccountNum]->getMyCard() });
    }


    //ATM선언 전 primary bank pointer, bankmap, card pointer가 준비되어 있어야 함
    //ATM 선언
    map<string, ATM*> ATMmap;
    int ATMNum;
    string ATMname;
    string AdminCardIn;
    string InputPrimaryBank;
    cout << "ATM을 설정하겠습니다" << endl;
    cout << "몇개의 ATM을 만드시겠습니까?" << endl;
    cin >> ATMNum;
    for (int i = 0; i < ATMNum; i++) {
        //Primary Bank Setting
        cout << i + 1 << "번째 ATM을 만들겠습니다." << endl;
    BacktoATMSET:
        cout << "아래 중 ATM의 주거래 은행을 선택하세요" << endl;
        cout << "[";
        for (auto iter = InputBankMap.begin(); iter != InputBankMap.end(); iter++) {
            cout << iter->first << " ";
        };
        cout << "]" << endl;
        cin >> InputPrimaryBank;
        cout << "ATM의 이름을 설정하세요." << endl;
        cin >> ATMname;
    BacktoAdminCardSET:
        cout << "ATM의 Admin Card의 카드 번호를 입력하세요." << endl;
        cin >> AdminCardIn;

        Bank* ba;
        auto bankIter = InputBankMap.find(InputPrimaryBank);
        if (bankIter != InputBankMap.end()) {
            ba = bankIter->second;
        }
        else {
            cout << "존재하지 않는 은행입니다" << endl;  // This line doesn't seem to do anything
            goto BacktoATMSET;
        }

        /*
        auto cardIter = inputCardMap.find(AdminCard);
        if (cardIter != inputCardMap.end()) {
            c = cardIter->second;
        }
        else {
            cout << "존재하지 않는 은행입니다" << endl;  // This line doesn't seem to do anything
            goto BacktoAdminCardSET;
        }*/




        ATM* n = new ATM(ba, InputBankMap, AdminCardIn);
        ATMmap.insert({ ATMname, n });
    }
    Global* myGlobal = new Global(AccountMap, ATMmap);
    for (auto& i : ATMmap) {
        i.second->SetGlobal(myGlobal);
    }

    bool isATMworking = true;
    while (isATMworking) {
        //display
        for (const auto& pair : AccountMap) {
            cout << "[Account " << pair.first << "] " << pair.second->getBalance() << endl;
        }
        for (const auto& pair : ATMmap) {
            cout << "[ATM " << pair.first << "] " << endl;
            pair.second->ShowAvailableCash();
        }

        //select ATM
        string UsedATM;
        cout << "Write the name of an ATM that you want to use." << endl;
        cin >> UsedATM;

        if (UsedATM == "x") {
            myGlobal->Display();
            cout << "Write the name of an ATM that you want to use." << endl;
            cin >> UsedATM;


        }

        ATMmap[UsedATM]->Start();

        char isNew;
        while (true) {
            string isNewOkay;
            cout << "Do you want to make new account or new ATM? (y or n)" << endl;
            cin >> isNewOkay;
            if (isNewOkay == "n") {
                break;
            }
            cout << "[a] Make new account [b] Make new ATM" << endl;;
            cin >> isNew;

            if (cin.fail() == true) {
                cout << "It's valid character. Please reselect character." << endl;
                cin.clear();
                cin.ignore(100, '\n');
                continue; //for문 다시 돌아가서 선택하게 하기.
            }
            else if (isNew == 'x') {
                myGlobal->Display();
                continue;
            } else if (isNew == 'a'){
                cout << "Account를 선언하겠습니다" << endl;
                cout << "몇개의 Account를 만드시겠습니까?" << endl;
                cin >> NumofAccount;
                for (int i = 0; i < NumofAccount; i++) {
                    cout << "계좌" << (i + 1) << "의 주거래 은행을 알려주세요" << endl;
                    cin >> pb;
                    cout << "계좌번호를 입력해주세요" << endl;
                    cin >> AccountNum;
                    cout << "계좌 소유주의 성명을 입력해주세요" << endl;
                    cin >> ownername;
                    cout << "계좌 비밀번호를 입력해주세요" << endl;
                    cin >> pw;
                    //const string& accountNum, const string& password, const string& ownerName, Bank* bank
                    map<string, Bank*> inputTMP;
                    inputTMP[pb] = InputBankMap[pb];
                    //Account(AccountNum, pw, ownername, inputTMP); //수정중
                    AccountMap.insert({ AccountNum, new Account(AccountNum, pw, ownername, inputTMP[pb]) });//stop
                    map<string, Account*> bankin;
                    bankin[AccountNum] = AccountMap[AccountNum];
                    InputBankMap[pb]->setAccounts(bankin);

                    //Card 선언
                    cout << "카드번호를 입력하세요" << endl;
                    string cardNumber;
                    cin >> cardNumber;
                    AccountMap[AccountNum]->setMyCard(new Card(cardNumber, AccountNum));
                    inputCardMap.insert({ cardNumber, AccountMap[AccountNum]->getMyCard() });
                }
                break;
            }
            else if (isNew == 'b') {
                int ATMNum1;
                string ATMname1;
                string AdminCardIn1;
                string InputPrimaryBank1;
                cout << "ATM을 설정하겠습니다" << endl;
                cout << "몇개의 ATM을 만드시겠습니까?" << endl;
                cin >> ATMNum1;
                for (int i = 0; i < ATMNum1; i++) {
                    //Primary Bank Setting
                    cout << i + 1 << "번째 ATM을 만들겠습니다." << endl;
                    while (true) {
                        cout << "아래 중 ATM의 주거래 은행을 선택하세요" << endl;
                        cout << "[";
                        for (auto iter = InputBankMap.begin(); iter != InputBankMap.end(); iter++) {
                            cout << iter->first << " ";
                        };
                        cout << "]" << endl;
                        cin >> InputPrimaryBank1;


                        Bank* ba;
                        auto bankIter = InputBankMap.find(InputPrimaryBank1);
                        if (bankIter != InputBankMap.end()) {
                            ba = bankIter->second;
                            break;
                        }
                        else {
                            cout << "존재하지 않는 은행입니다." << endl;
                            continue;
                        }

                    cout << "ATM의 이름을 설정하세요." << endl;
                    cin >> ATMname1;

                    cout << "ATM의 Admin Card의 카드 번호를 입력하세요." << endl;
                    cin >> AdminCardIn1;

                    ATM* n = new ATM(ba, InputBankMap, AdminCardIn);
                    ATMmap.insert({ ATMname, n });
                    }
                    
                }
                break;
            }
            else {
                cout << "It's valid character. Please reselect character." << endl;
                continue;
            }
        }
        

        //quit?
        char isQuit;
        cout << "Do you want to terminate current program? (y, n)" << endl;
        cin >> isQuit;
        if (isQuit == 'n') {
            isATMworking = true;
        }
        else if (UsedATM == "x") {
            myGlobal->Display();
            cout << "Do you want to terminate current program? (y, n)" << endl;
            cin >> isQuit;
            if (isQuit == 'n') {
                isATMworking = true;
            }
            else { isATMworking = false; }

        }
        else { isATMworking = false; }
    }

    return 0;
}

