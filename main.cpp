#include <iostream>
#include <string.h>
#include <unordered_map>

using namespace std;



// -------------------------------[Session] class-----------------------------------
// -------------------------------[Session] class-----------------------------------
=======
class ATM;
class Session;
class Card;
class Transaction;
class Bank;
class Account;

class Session {
private:
public:
};



// -------------child of Session class ---------------
class KoreanSession {
private:
public:

};

class EnglishSession {
private:
public:

};




// -------------------------------[Transaction] class-----------------------------------
// -------------------------------[Transaction] class-----------------------------------
class Transaction{
private: 
	ATM* CurrentATM;
public:
	void Withdraw(int, string, string, int, string);//amount, bank, username, AccountNum, password //bank에서 계좌 확인 후 limit 안넘으면 출금, bank 확인해 fee 결정해 빼고 출금, ATM의 available_cash 감소, 최대 50만원 withdraw 가능    
	void Transfer(string, string, int, string, string, int); //bank1, username, AccountNum, password, bank2, amount//fee 고려, amount+fee 잔액 확인
	void Open_Account(string, string, int, string, int, int);//bank, username, AccountNum, password, account number, available fund
	void Deposit(int, account*);//cash total 개수, 계좌
	
	//유리의 일거리
	void CheckInput();//cash인지 check인지 확인해 CheckCash 또는 CheckCheck 호출
	void CheckCash(mapset, string, string, string, string);//cash 종류별 개수, bank, username, accountnum, password
	void CheckCheck(int[], string, int, string); //amount, username, accountnum, password
	void Display(int, string, int, int, string, bool); //이동한 금액, username, AccountNum, card number, bank, externalFile=False 필요여부//이름 받아 transaction 결과 보여줌, 각 transaction에서 호출, external file True면 external file로 출력
	void Authorize(int, string, int); //card number, username, AccountNum//함수 내에서 password 요구 및 확인 필요, 최대 3번 요구 후 return card
	void EndSession(); // History에서 withdraw 3번 넘으면 session 종료
	
};



//----------------child of Transaction----------------------

=======



class withdrawTransaction {
private :

public:


};


class DepositTransaction {
private :

public:

};


class Transfer {
private :

public:

} ;



// -------------------------------[ATM] class-----------------------------------
// -------------------------------[ATM] class-----------------------------------
class ATM{
private: 
	const int SerialNumber;
	string PrimaryBank;
	string NonPrimaryBank = [];
	map<int, int> AvailableCash;
	Account* admin;
	static string* History = [];
	bool IsBilingual = false;
	bool IsMultiBank = false;
	static int NumberOfATM;
	map<string, Bank*> BankMap; 
	

//int DP_2 = 1000; int WD_1 = 1000; int WD_2 = 2000;int TR_1_1 = 2000;int TR_1_2 = 3000;int TR_2_2 = 4000;int Cash_TR = 5000;

public:
//영우의 일거리
	ATM()//기본값으로 설정, Bank는 아무거나 설정
	ATM(int, Bank*, map, bool=false, bool=false, map);//SerialNumber, PrimaryBank, NonPrimaryBank map, multibank 여부, bilingual 여부, initial fund map
	~ATM();
	int get_SerialNumber();
	bool get_IsMultiBank();
	map<int, int> get_AvailableCash();
	void check_admin(int)//card number //admin이면 transaction history 메뉴 보여줌
	int get_cash();
	static string* get_History();
	//card 받는 함수 추가하기!
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
//어디 은행인지 알려주는 기능 
// 뱅크가 어카운트에 대한 포인터가 있어야함.  ( 어카운트가 뱅크에 대한 포인터로 변경 ! ->  )
// [유리] Bank constructor/destructor가 필요합니다!
// fee 도 필요 ?



private:
    unordered_map<string, Account> accounts; // 계좌 번호를 키로 사용
    Card bankCard;
    string bankName;

public:

    // Bank 클래스의 생성자
    Bank(const std::string& name) : bankName(name) {
	// 생성자에서 필요한 초기화 작업 수행
        // 예: 특정 멤버 변수 초기화, 메모리 할당 등
    }


    // Account 생성 및 추가
    void createAccount(const string& accountNum, const string& password, const string& ownerName) {
        // 이미 존재하는 계좌인지 확인하고 추가
        if (accounts.find(accountNum) == accounts.end()) {
            accounts[accountNum] = Account(accountNum, password, ownerName, this);
        }
    }

    // 사용자 정보를 모두 출력하는 함수 (특정 사용자의 모든 계정 정보를 출력하는 함수)
    void allAccount(const string& username) {
        cout << "사용자 " << username << "의 모든 계정 정보:" << endl;
        for (const auto& entry : accounts) {
            const Account& account = entry.second;
            if (account.getOwnerName() == username) {
                cout << "계좌 번호: " << account.getAccountNum() << ", ";
                cout << "잔액: " << account.getBalance() << endl;
            }
        }
    }

    // 사용자 정보를 확인하는 함수 (사용자 정보를 확인하고, 주어진 사용자 이름, 계좌 번호, 비밀번호와 일치하는지 여부를 반환하는 함수) 
    bool verifyUser(const string& username, const string& accountNum, const string& password) {
        auto it = accounts.find(accountNum);
        if (it != accounts.end()) {
            const Account& account = it->second;
            return (account.getOwnerName() == username && account.verifyPW(password));
        }
        return false; // 사용자 확인 실패
    }

    // 계정 정보를 확인하는 함수(계정 정보를 확인하고, 주어진 계좌 번호와 비밀번호가 일치하는지 여부를 반환하는 함수입니다.)
    bool verifyAccount(const string& accountNum, const string& password) {
        auto it = accounts.find(accountNum);
        return (it != accounts.end() && it->second.verifyPW(password));
    }

    // 계좌 존재 여부 확인 (주어진 계좌 번호가 은행에 존재하는지 여부를 확인하는 함수)
    bool accountExists(int accountNum) {
        return accounts.find(accountNum) != accounts.end();
    }

	
    // 은행 이름 리턴 함수
    string getBankName() const {
        return bankName;
    }

 //session withdraw에서 if (bank->accountExists(accountNum))  이런식으로 하면 될합니다.


}
=======




    // Bank 클래스의 소멸자
    ~Bank() {
        // 소멸자에서 리소스 정리 작업 수행
        // 예: 동적으로 할당된 메모리 해제 등
    }


};


// -------------------------------[Account] class-----------------------------------
// -------------------------------[Account] class-----------------------------------

class  {

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
        } else {
            cout << "잔액이 부족합니다." << std::endl;
        }
    }
};








///--------------------------------method-------------------------------------

///--------------------------------method-------------------------------------

///--------------------------------method-------------------------------------




//-------------------------------------ATM-------------------------------------------
//Youngwoo
ATM::ATM() : ATM(NumberOfATM, "Default", false, false) {
	Bank* bankpointer;
	cout << "primary bank name: " << endl;
	cin >> PrimaryBank;
	cout << "primary bank pointer: " << endl;
	cin >> bankpointer;
	BankMap.insert({PrimaryBank, bankpointer});
	cout << "Multibank? y or n" << endl;
	cin >> tmp;
	while(1) {
	        if (tmp == "y") {
			IsMultiBank = true; 
			//main함수의 banklist에 들어있는 다른 은행들을 nonprimarybank list와 bankmap에 넣기
			break;}
	        else if(tmp == "n") {IsMultiBank = false; break;}
	        else{
	            cout << "You should input the value y or n. Case sensitive." << endl;
	            cout << "Multibank? y or n" << endl;
	            cin >> tmp;
	        }
	}
	cout << "Bilingual? y or n" << endl;
	cin >> tmp;
	while(1) {
	        if (tmp == "y") {IsBilingual = true; break;}
	        else if(tmp == "n") {IsBilingual = false; break;}
	        else{
	            cout << "You should input the value y or n. Case sensitive." << endl;
	            cout << "Multibank? y or n" << endl;
	            cin >> tmp;
		}
	};

}
ATM::ATM(int snum, Bank* primary, map allmap, bool multibank=false, bool bilingual=false, map InitialFund) {
	//SerialNumber, PrimaryBank, NonPrimaryBank map, multibank 여부, bilingual 여부, initial fund map
	SerialNumber = snum;
	PrimaryBank = primary;
	IsMultiBank = multibank;
	//main함수의 banklist에 들어있는 다른 은행들을 nonprimarybank list와 bankmap에 넣기
	IsBilingual = bilingual;
	BankMap = allmap;
	//[논의 필요]string NonPrimaryBank list를 만들어야 하는지?
	NumberOfATM++;

}
ATM::~ATM() {
	//[유리] 완성해주세요
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
map<int, int> ATM::get_AvailableCash(){
	return AvailableCash;
}
//-------------------------------------Session---------------------------------------
void Session::Withdraw(int, string, string, int, string) {
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
void Session::Transfer(string, string, int, string, string, int) {
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
void Session::Open_Account(string, string, int, string, int) {
	//bank, username, AccountNum, password, (account number->있었는데 삭제, available fund
	cout << "은행 이름을 입력하세요." << endl;
	cin << string bankName << endl;
	cout << "사용자 이름을 입력하세요." << endl;
	cin << string userName << endl;
	cout << "비밀번호를 입력하세요." << endl;
	cin << int pw << endl;
	Account(bankName, userName, pw);
}
void Session::Deposit(int, account*) {
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
Session::CheckCash() {
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
Session::CheckCheck() {
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

Session::Display(int TransactionAmount, string Username, AccountNum, CardNum, myBank, ExternalFile=false){
//이름 받아 transaction 결과 보여줌, 각 transaction에서 호출, external file True면 external file로 출력

    	cout << "=================Transaction Result=================" << endl;
    	cout << "User Name : " << Username << endl;
    	cout << "Account : " << AccountNum << endl;
    	cout << "Card : " << CardNum << endl;
    	cout << "From "<< myBank << " " << TransactionAmount << "Won" << endl;
}

Session::Authorize(string Username, int AccountNum, string Password, Bank* Bank){
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
	//<bank 이름 string,bank pointer>로 구성된 map 형성
	//[수정 필요]Bank constructor가 지정되면 그에 맞춰 수정되어야 할 부분!
	//[수정 필요]은행의 이름이 한국어로 들어오는 input도 고려해야 하는가?
	int BankNum;
	string InputBankName1;
	map <string, Bank*> InputBankMap;
	cout << "BANK를 선언하겠습니다" << endl;
	cout << "몇개의 은행을 만드시겠습니까? << endl;
	cin >> BankNum;
	for (int i=0; i<BankNum; i++){
		cout << "은행의 이름을 입력해주세요" << endl;
		cin >> BankName1;
		Bank new = Bank BankName1+"BANK";
		InputBankMap.insert({BankName1,new});
	};

	//ATM 선언
	//[수정 필요]논의 후 수정
	int ATMNum;
	string InputPrimaryBank;
	cout << "ATM을 설정하겠습니다" << endl;
	cout << "몇개의 ATM을 만드시겠습니까?" << endl;
	cin >> ATMNum;
	for (int i=0; i<ATMNum; i++){

		//============================This?====================================
		//Primary Bank Setting
		cout << "아래 중 ATM의 주거래 은행을 선택하세요" << endl;
		cout << "[";
		for (int iter=InputBankMap.begin(); iter != InputBankMap.end() ; iter++){
			cout << iter->first << ",";
		};
		cout << "]" << endl;
		cin >> InputPrimaryBank;

		//Single? Multi?
		bool InputSingle
		cout << "Single ATM은 1, Multi ATM은 2를 선택해주세요" << endl;
		cin >> InputSingle;
		//============================OR this?=================================
		cout << "serial number, primary bank 이름, multibank 여부, bilingual 여부를 입력해주세요" << endl;
		//ATM(int snum, Bank* primary, bool maltibank=false, bool bilingual=false)
		//=====================================================================
	}
	ATM ShinhanATM;
	ATM DaeguATM;
	
	cout << "All ATM : " <<
		선택하세요

		
	
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




