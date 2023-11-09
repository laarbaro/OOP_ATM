#include <iostream>
#include <string.h>

using namespace std;

class ATM{
private: 
    const int SerialNumber;
    string PrimaryBank;
    string NonPrimaryBank = [];
    int AvailableCash = 0;
		int 2_DP = 1000;
    int 1_WD = 1000;
    int 2_WD = 2000;
    int 1_1_TR = 2000;
    int 1_2_TR = 3000;
    int 2_2_TR = 4000;
    int Cash_TR = 5000;
    Account* admin;
    static string[] History = [];
    bool IsBilingual = false;
		bool IsMultiBank = false;
		static int NumberOfATM;

public:
		//영우의 일거리
    ATM()//기본값으로 설정, Bank는 아무거나 설정
    ATM(int, Bank*, bool=false, bool=false);//SerialNumber, PrimaryBank, multibank 여부, bilingual 여부
    ~ATM();
		int get_SerialNumber();
    bool get_IsMultiBank();
		void Withdraw(int, string, string, int, string)//amount, bank, username, AccountNum, password //bank에서 계좌 확인 후 limit 안넘으면 출금, bank 확인해 fee 결정해 빼고 출금, ATM의 available_cash 감소, 최대 50만원 withdraw 가능    
		void Transfer(string, string, int, string, string, int) //bank1, username, AccountNum, password, bank2, amount//fee 고려, amount+fee 잔액 확인
    void Open_Account(string, string, int, string, int, int)//bank, username, AccountNum, password, account number, available fund
		void Deposit(int, account*);//cash total 개수, 계좌

	  //유리의 일거리
		void CheckInput();//cash인지 check인지 확인해 CheckCash 또는 CheckCheck 호출
    void CheckCash(mapset, string, string, string, string);//cash 종류별 개수, bank, username, accountnum, password
    void CheckCheck(int[], string, int, string);//amount, username, accountnum, password
    void Display(int, string, int, int, string, bool)//이동한 금액, username, AccountNum, card number, bank, externalFile=False 필요여부//이름 받아 transaction 결과 보여줌, 각 transaction에서 호출, external file True면 external file로 출력
    void Authorize(int, string, int)//card number, username, AccountNum//함수 내에서 password 요구 및 확인 필요, 최대 3번 요구 후 return card
    void EndSession() // History에서 withdraw 3번 넘으면 session 종료
    void check_admin(int)//card number //admin이면 transaction history 메뉴 보여줌
		int get_cash();
		static string[] get_History();

		
}

//Youngwoo
ATM::ATM() : ATM(NumberOfATM, "Default", false, false) {
    //
}
ATM::ATM(int snum, Bank* primary, bool maltibank=false, bool bilingual=false) {
    //SerialNumber, PrimaryBank, multibank 여부, bilingual 여부
    SerialNumber = snum;
    PrimaryBank = primary;
    IsMultiBank = multibank;
    IsBilingual = bilingual;
    NumberOfATM++;
}
ATM::~ATM() {
    //
    NumberOfATM--;
    //detach?
}
int ATM::get_SerialNumber() {
    return SerialNumber;
}
bool ATM::get_IsMultiBank() {
    return IsMultiBank;
}
void ATM::Withdraw(int, string, string, int, string) {
    //amount, bank, username, AccountNum, password
    //bank에서 계좌 확인 후 limit 안넘으면 출금, bank 확인해 fee 결정해 빼고 출금, ATM의 available_cash 감소, 최대 50만원 withdraw 가능
    cout << "출금하실 금액을 입력하세요." << endl;
    cin >> int w;
    if (w < account.getBalance()) {
        cout << "잔액이 부족합니다." << endl;
    }
    else if (AvailableCash < w) {
        cout << "기기의 인출 가능 금액이 부족합니다. 관리자에게 문의하세요." << endl;
    }
    else {
        account.Withdraw(w+fee);
        AvailableCash -= w;
        withdrawalN--;
        cout << w << "원이 인출되었습니다." << endl;
    }
}
void ATM::Transfer(string, string, int, string, string, int) {
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
void ATM::Open_Account(string, string, int, string, int) {
    //bank, username, AccountNum, password, (account number->있었는데 삭제, available fund
    cout << "은행 이름을 입력하세요." << endl;
    cin << string bankName << endl;
    cout << "사용자 이름을 입력하세요." << endl;
    cin << string userName << endl;
    cout << "비밀번호를 입력하세요." << endl;
    cin << int pw << endl;
    Account(bankName, userName, pw);
}
void ATM::Deposit(int, account*) {
    //cash total 개수, 계좌
    cout << "입금하실 금액을 입력하세요." << endl;
    cin >> int d;
    if (d > limit) {
        cout << "입금가능한 금액을 초과하였습니다." << endl;
    }
    else {
        accout.Deposit(d-fee);
        AvailableCash += d;
        cout << d << "원이 입금되었습니다." << endl;
    }
}

//Youri
ATM::CheckCash() {
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

    //Receiving Account
    cout << "====================Cash Saving====================" << endl;
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
        cout << " Total Amount of Saving : " << Bank1->getAccount(AccountNum1)->Amount << endl;
    } else {
        cout << "Failed to Deposit." << endl;
    }
    cout << "===Thanks for Using Deposit Service of this ATM====" << endl;
}

ATM::CheckCheck() {
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
    
    //Receiving Account
    cout << "====================Check Saving====================" << endl;
    cout << "Which Bank do you want to deposit?" << endl;
    cin >> Bank1;
    cout <<"What is your name?" << endl;
    cin >> Username1;
    cout << "Please write your Account Number and Password" << endl;
    cin >> AccountNum1, Password1;

    cout << "Authorizing your account..." << endl;
    if Authorize(Username1, AccountNum1, Password1, Bank1) {
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
        cout << " Total Amount of Saving : " << Bank1->getAccount(AccountNum1)->Amount << endl;
    } else {
        cout << "Failed to Deposit." << endl;
    }
    cout << "===Thanks for Using Deposit Service of this ATM====" << endl;
}

ATM::Display(int TransactionAmount, string Username, AccountNum, CardNum, myBank, ExternalFile=false){
    //이름 받아 transaction 결과 보여줌, 각 transaction에서 호출, external file True면 external file로 출력

    cout << "=================Transaction Result=================" << endl;
    cout << "User Name : " << Username << endl;
    cout << "Account : " << AccountNum << endl;
    cout << "Card : " << CardNum << endl;
    cout << "From "<< myBank << " " << TransactionAmount << "Won" << endl;
}

ATM::Authorize(string Username, int AccountNum, string Password, Bank* Bank){
    string UsernameFromBank = Bank->getAccount(AccountNum)->getUserName
    string UserPassword = Bank->getAccount(AccountNum)->getPassword
    if (UsernameFromBank==Username){
        if (UserPassword==password){
            return True;
        }else{
            return False;
        }
    }else{
        return False;
    }
    
}

int main() {
		return 0;
}
