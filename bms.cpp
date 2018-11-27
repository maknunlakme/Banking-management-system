//***************************************************************************
//_____________________Banking Management System_____________________________
//***************************************************************************
/*Included features: class, abstract class, inheritance, multilevel inheritance
multiple inheritance, passing object in function, static variable, bool type variable,
constant member functions, function overloading, operator overloading,
function overriding, constructor, derived class constructor,destructor,
data conversion, base class pointer, pure virtual function, switch statement */
#include<iostream>
using namespace std;
#include<string>
#include<stdio.h>
#define BRANCH 3
#define ACCOUNT 10
#define ACCOUNTANT 2
#define STAFF 3
#define EMPLOYEE 9
//Account Holder class
//--------------------------------------------------------------------------------------------------
class AccHolder
{
protected:
    string Name;
    float Balance,LastWithdraw,LastDeposit;
    int AccountID;
    static int CountID; //Static Variable of setting Account ID
public:
    AccHolder(): AccountID(CountID+1),Balance(0),LastWithdraw(0),LastDeposit(0)// Constructor
    {
        CountID++;
        if(CountID%100==ACCOUNT)
            CountID+=(100-ACCOUNT);
    }
    ~AccHolder()// Destructor
    {   }
    //Member functions
    void SetBalance();
    float GetBalance()const;//constant member function
    void ShowBalance()const;
    void UpdateBalance(int);
    int GetAccountID()const;
    void ShowAccountID()const;
    void SetName();
    string GetName()const;
    void ShowName()const;
    void WithdrawAndUpdate();
    void ShowLastWithdraw()const;
    void DepositAndUpdate();
    void ShowLastDeposit()const;
    void CalcInterestAndUpdate(int);
    void operator +=(AccHolder);//Overloading += operator
    operator float()const;//data conversion from object to float
    friend ostream & operator << (ostream &out, const AccHolder Account[][ACCOUNT]);//Overloading << Operator
};
//Branch Info class
//----------------------------------------------------------------------------------------------------------------
class BranchInfo
{
private:
    float BranchTotal;
public:
    BranchInfo() : BranchTotal(0.0)
    {   }
    ~BranchInfo()
    {   }
    void CalcBranchTotal(AccHolder [][ACCOUNT], int, int, int);//Passing an object
    float GetBranchTotal()const;
    void ShowBranchTotal(int)const;
};
//Loan Taker Class:Abstract Class
//---------------------------------------------------------------------------------------
class LoanTaker
{
protected:
    float Loan,LoanLimit;
public:
    LoanTaker() : Loan(0.0)
    {   }
    ~LoanTaker()
    {   }
    virtual void Show()=0;//Pure virtual function
    void CalcLoanLimit(float);
    void TakingLoan();
    float GetLoan()const;
    void ShowLoan()const;
};
//Loan Taking Account Holder Class
//-------------------------------------------------------------------------------------
class LoanTakingAccHolder : public AccHolder, public LoanTaker//Multiple Inheritance
{
private:
    int AccountID;
    static int LoanAccCountID;
public:
    LoanTakingAccHolder() : AccHolder(),LoanTaker(),AccountID(LoanAccCountID+1)//Derived Class Constructor
    {
        LoanAccCountID++;
        if(LoanAccCountID%100==ACCOUNT)
            LoanAccCountID+=(100-ACCOUNT);
    }
    ~LoanTakingAccHolder()
    {   }
    void UpdateLoanBalance();
    int GetAccountID();
    int ShowAccountID();
    void Show()// Overriding pure virtual function
    {   }
    friend ostream & operator << (ostream &out, const LoanTakingAccHolder LoanTakingAccount[][ACCOUNT]);//Overloading << Operator
};
//Employee Info Class: Abstract Class
//------------------------------------------------------------------------------------------------------------------------------------
class EmployeeInfo
{
protected:
    string Name;
    int ID;
    float Bonus;
public:
    EmployeeInfo(): ID(0)
    {   }
    EmployeeInfo(int id): ID(id)//Overloaded function
    {   }
    ~EmployeeInfo()
    {   }
    virtual void Show()=0;//Pure virtual function
    void SetName();
    string GetName()const;
    void ShowName()const;
    void SetID();
    int GetID()const;
    void ShowID()const;
};
//Bonus Employee Info Class: Abstract Class
//--------------------------------------------------------------------------------------
class BonusEmployeeInfo: public EmployeeInfo//Inheritance
{
protected:
    float Bonus;
public:
    BonusEmployeeInfo(): EmployeeInfo(),Bonus(0)
    {   }
    BonusEmployeeInfo(int id): EmployeeInfo(id),Bonus(0)
    {   }
    ~BonusEmployeeInfo()
    {   }
    void virtual Show()=0;//Pure virtual function
    void CalcBonus(AccHolder [][ACCOUNT], int, int, int, int);
    float GetBonus()const;
    void ShowBonus()const;
};
//Non Bonus Employee Info Class: Abstract Class
//-------------------------------------------------------------------------------------
class NonBonusEmployeeInfo: public EmployeeInfo//Inheritance
{
public:
    NonBonusEmployeeInfo():EmployeeInfo()
    {   }
    NonBonusEmployeeInfo(int id): EmployeeInfo(id)
    {   }
    ~NonBonusEmployeeInfo()
    {   }
    virtual void Show()=0;//Pure virtual function
};
//Accountant Info Class
//-------------------------------------------------------------------------------------------
class AccountantInfo: public BonusEmployeeInfo//Multilevel Inheritance
{
public:
    AccountantInfo(): BonusEmployeeInfo()
    {   }
    AccountantInfo(int id): BonusEmployeeInfo(id)
    {   }
    ~AccountantInfo()
    {   }
    void Show()// Overriding pure virtual function
    {   }
    void SetName(int, int);
    void ShowName(int, int)const;
    void SetID(int, int);
    void ShowID(int, int)const;
    void ShowBonus(int, int)const;//Overriding functions
};
class ManagerInfo: public BonusEmployeeInfo
{
public:
    ManagerInfo(): BonusEmployeeInfo()
    {   }
    ManagerInfo(int id): BonusEmployeeInfo(id)
    {   }
    ~ManagerInfo()
    {   }
    void Show()// Overriding pure virtual function
    {   }
    void SetName(int);
    void ShowName(int)const;
    void SetID(int);
    void ShowID(int)const;
    void ShowBonus(int)const;//Overriding functions
};
class OfficeStaffInfo: public NonBonusEmployeeInfo
{
public:
    OfficeStaffInfo(): NonBonusEmployeeInfo()
    {   }
    OfficeStaffInfo(int id): NonBonusEmployeeInfo(id)
    {   }
    ~OfficeStaffInfo()
    {   }
    void Show()// Overriding pure virtual function
    {   }
    void SetName(int, int);
    void ShowName(int, int)const;
    void SetID(int, int);
    void ShowID(int, int)const;//Overriding functions
};
class OwnerInfo: public BonusEmployeeInfo
{
public:
    OwnerInfo(): BonusEmployeeInfo()
    {   }
    OwnerInfo(int id): BonusEmployeeInfo(id)
    {   }
    ~OwnerInfo()
    {   }
    void Show()// Overriding pure virtual function
    {   }
    void SetName();
    void ShowName()const;
    void SetID();
    void ShowID()const;
    void CalcBonus(AccHolder [][ACCOUNT], int);//Overriding functions
};
//All necessary functions
//-------------------------------------------------------------------------------------
int AccHolder :: CountID = 110100;
int LoanTakingAccHolder :: LoanAccCountID = 120100;
void AccHolder::SetBalance()
{
    cout<<"Enter your Balance:";
    cin>>Balance;
    fflush(stdin);
}
float AccHolder::GetBalance()const
{
    return Balance;
}
void AccHolder::ShowBalance()const
{
    cout<<"Your Balance is:"<<Balance<<endl;
}
void AccHolder::UpdateBalance(int balance)
{
    Balance+=balance;
}
int AccHolder::GetAccountID()const
{
    return AccountID;
}
void AccHolder::ShowAccountID()const
{
    cout<<"Your Account ID is:"<<AccountID<<endl;
}
void AccHolder::SetName()
{
    cout<<"Enter your name:";
    getline(cin,Name);
    fflush(stdin);
}
string AccHolder::GetName()const
{
    return Name;
}
void AccHolder::ShowName()const
{
    cout<<"Name:"<<Name<<endl;
}
static int CountBranch=0;
static int CountAccount=0;
void AccHolder::WithdrawAndUpdate()
{
    cout<<"How much you want to withdraw "<<Name<<":";
    cin>>LastWithdraw;
    fflush(stdin);
    if(LastWithdraw<=Balance)
    {
        cout<<"You can withdraw the amount"<<endl;
        Balance-=LastWithdraw;
    }
    else
    {
        cout<<"You cannot withdraw the amount"<<endl;
    }
}
void AccHolder::ShowLastWithdraw()const
{
    cout<<"Your last withdraw is:"<<LastWithdraw<<endl;
}
void AccHolder::DepositAndUpdate()
{
    cout<<"How much you want to deposit "<<Name<<":";
    cin>>LastDeposit;
    fflush(stdin);
    Balance+=LastDeposit;
    cout<<"Your amount is deposited"<<endl;
}
void AccHolder::ShowLastDeposit()const
{
    cout<<"Your last deposit is:"<<LastDeposit<<endl;
}
void AccHolder::CalcInterestAndUpdate(int Interest)
{
    cout<<"Calculating Interest"<<endl;
    Balance+=Balance*(.01*Interest);
}
void AccHolder:: operator +=(AccHolder Account)//Overloading += operator
{
    int Temp;
    Temp=Account.GetBalance();
    Balance+=Temp;
}
AccHolder:: operator float()const//data conversion from object to float
{
    return Balance;
}
ostream & operator << (ostream &out, const AccHolder Account[BRANCH][ACCOUNT])//Overloading << operator
{
    int i,j;
    for(i=0;i<BRANCH;i++)
    {
        for(j=0;j<ACCOUNT;j++)
        {
            if(Account[i][j].Balance!=0)
            {
                out<<"Account ID: "<<Account[i][j].AccountID<<endl;
                out<<"Name: "<<Account[i][j].Name<<endl;
                out<<"Balance: "<<Account[i][j].Balance<<endl;
                out<<"Last Withdraw: "<<Account[i][j].LastWithdraw<<endl;
                out<<"Last Deposit: "<<Account[i][j].LastDeposit<<endl;
            }
        }
    }
    return out;
}
static int LoanCountBranch=0;
static int LoanCountAccount=0;
void LoanTakingAccHolder::UpdateLoanBalance()
{
    Balance+=Loan;
}
int  LoanTakingAccHolder::GetAccountID()
{
    return AccountID;
}
int LoanTakingAccHolder::ShowAccountID()
{
    cout<<"Account ID: "<<AccountID<<endl;
}
ostream & operator << (ostream &out, const LoanTakingAccHolder LoanTakingAccount[BRANCH][ACCOUNT])
{
    int i,j;
    for(i=0;i<BRANCH;i++)
    {
        for(j=0;j<ACCOUNT;j++)
        {
            if(LoanTakingAccount[i][j].Balance!=0)
            {
                out<<"Account ID: "<<LoanTakingAccount[i][j].AccountID<<endl;
                out<<"Name: "<<LoanTakingAccount[i][j].Name<<endl;
                out<<"Balance: "<<LoanTakingAccount[i][j].Balance<<endl;
                out<<"Last Withdraw: "<<LoanTakingAccount[i][j].LastWithdraw<<endl;
                out<<"Last Deposit: "<<LoanTakingAccount[i][j].LastDeposit<<endl;
            }
        }
    }
    return out;
}
void BranchInfo::CalcBranchTotal(AccHolder Account[BRANCH][ACCOUNT], int BranchNo, int AccountStart, int AccountEnd)
{
    int j;
    AccHolder TempAccount;
    for(j=AccountStart-1;j<AccountEnd;j++)
    {
        TempAccount+=Account[BranchNo][j];
    }
    BranchTotal=TempAccount;
}
float BranchInfo::GetBranchTotal()const
{
    return BranchTotal;
}
void BranchInfo::ShowBranchTotal(int BranchNo)const
{
    cout<<"Total amount of Branch "<<BranchNo+1<<" is: "<<BranchTotal<<endl;
}
void LoanTaker::CalcLoanLimit(float balance)
{
    LoanLimit=.2*balance;
}
void LoanTaker::TakingLoan()
{
    float TempLoan;
    cout<<"How much loan you want to take: ";
    cin>>TempLoan;
    fflush(stdin);
    if(TempLoan<=LoanLimit)
    {
        cout<<"You can loan the amount"<<endl;
        Loan=TempLoan;
    }
    else
        cout<<"You cannot loan the amount"<<endl;

}
void EmployeeInfo:: SetName()
{
    cout<<"Enter Name: ";
    getline(cin,Name);
    fflush(stdin);
}
string EmployeeInfo:: GetName()const
{
    return Name;
}
void EmployeeInfo:: ShowName()const
{
    cout<<"Name : "<<Name<<endl;
}
void EmployeeInfo::SetID()
{
    cout<<"Enter ID: ";
    cin>>ID;
    fflush(stdin);
}
int EmployeeInfo:: GetID()const
{
    return ID;
}
void EmployeeInfo:: ShowID()const
{
    cout<<"ID: "<<ID<<endl;
}
void BonusEmployeeInfo::CalcBonus(AccHolder Account[BRANCH][ACCOUNT], int BranchNo, int AccountStart, int AccountEnd, int bonus)
{
    float Temp;
    BranchInfo TempBranch;
    TempBranch.CalcBranchTotal(Account, BranchNo, AccountStart, AccountEnd);
    Temp=TempBranch.GetBranchTotal();
    Bonus=Temp*(.01*bonus);
}
float BonusEmployeeInfo:: GetBonus()const
{
    return Bonus;
}
void BonusEmployeeInfo:: ShowBonus()const
{
    cout<<"Bonus: "<<Bonus<<endl;
}
static int CountAccountantBranch=0;
static int CountAccountantNo=0;
void AccountantInfo::SetName(int BranchNo, int AccountantNo)
{
    cout<<"Accountant "<<AccountantNo+1<<" Branch "<<BranchNo+1<<" ";
    EmployeeInfo::SetName();
}
void AccountantInfo::ShowName(int BranchNo, int AccountantNo)const
{
    cout<<"Accountant "<<AccountantNo+1<<" Branch "<<BranchNo+1<<" ";
    EmployeeInfo::ShowName();
}
void AccountantInfo::SetID(int BranchNo, int AccountantNo)
{
    cout<<"Accountant "<<AccountantNo+1<<" Branch "<<BranchNo+1<<" ";
    EmployeeInfo::SetID();
}
void AccountantInfo::ShowID(int BranchNo, int AccountantNo)const
{
    cout<<"Accountant "<<AccountantNo+1<<" Branch "<<BranchNo+1<<" ";
    EmployeeInfo::ShowID();
}
void AccountantInfo::ShowBonus(int BranchNo, int AccountantNo)const
{
    cout<<"Accountant "<<AccountantNo+1<<" Branch "<<BranchNo+1<<" ";
    BonusEmployeeInfo::ShowBonus();
}
static int CountManager=0;
void ManagerInfo::SetName(int BranchNo)
{
    cout<<"Manager of Branch "<<BranchNo+1<<" ";
    EmployeeInfo::SetName();
}
void ManagerInfo::ShowName(int BranchNo)const
{
    cout<<"Manager of Branch "<<BranchNo+1<<" ";
    EmployeeInfo::ShowName();
}
void ManagerInfo::SetID(int BranchNo)
{
    cout<<"Manager of Branch "<<BranchNo+1<<" ";
    EmployeeInfo::SetID();
}
void ManagerInfo::ShowID(int BranchNo)const
{
    cout<<"Manager of Branch "<<BranchNo+1<<" ";
    EmployeeInfo::ShowID();
}
void ManagerInfo::ShowBonus(int BranchNo)const
{
    cout<<"Manager of Branch "<<BranchNo+1<<" ";
    BonusEmployeeInfo::ShowBonus();
}
void OfficeStaffInfo::SetName(int BranchNo, int StaffNo)
{
    cout<<"Office Staff "<<StaffNo+1<<" Branch "<<BranchNo+1<<" ";
    EmployeeInfo::SetName();
}
void OfficeStaffInfo::ShowName(int BranchNo, int StaffNo)const
{
    cout<<"Office Staff "<<StaffNo+1<<" Branch "<<BranchNo+1<<" ";
    EmployeeInfo::ShowName();
}
void OfficeStaffInfo::SetID(int BranchNo, int StaffNo)
{
    cout<<"Office Staff "<<StaffNo+1<<" Branch "<<BranchNo+1<<" ";
    EmployeeInfo:: SetID();
}
void OfficeStaffInfo::ShowID(int BranchNo, int StaffNo)const
{
    cout<<"Office Staff "<<StaffNo+1<<" Branch "<<BranchNo+1<<" ";
    EmployeeInfo:: ShowID();
}
static int CountStaffBranch=0;
static int CountStaffNo=0;
void OwnerInfo::SetName()
{
    cout<<"Owner ";
    EmployeeInfo::SetName();
}
void OwnerInfo::ShowName()const
{
    cout<<"Owner ";
    EmployeeInfo::ShowName();
}
void OwnerInfo::SetID()
{
    cout<<"Owner ";
    EmployeeInfo::SetID();
}
void OwnerInfo::ShowID()const
{
    cout<<"Owner ";
    EmployeeInfo::ShowID();
}
void OwnerInfo::CalcBonus(AccHolder Account[BRANCH][ACCOUNT], int bonus)
{
    int i;
    float Temp;
    BranchInfo TempBranch;
    for(i=0;i<BRANCH;i++)
    {
        TempBranch.CalcBranchTotal(Account, i, 1, ACCOUNT);
        Temp=TempBranch.GetBranchTotal();
        Bonus+=Temp*(.01*bonus);
    }
}
//Main function
//----------------------------------------------------------------------------------------------
int main()
{
    //Necessary variables;
    int View;
    int i,j;
    float TempBalance;
    AccHolder Account[BRANCH][ACCOUNT];
    LoanTakingAccHolder LoanTakingAccount[BRANCH][ACCOUNT];
    BranchInfo Branch[BRANCH];
    AccountantInfo Accountant[BRANCH][ACCOUNTANT];
    ManagerInfo Manager[BRANCH];
    OwnerInfo Owner;
    OfficeStaffInfo OfficeStaff[BRANCH][STAFF];
    BonusEmployeeInfo *AllBonus[EMPLOYEE];//Base class pointer
    AllBonus[0]=&Manager[0];
    AllBonus[1]=&Manager[1];
    AllBonus[2]=&Manager[2];
    AllBonus[3]=&Accountant[0][0];
    AllBonus[4]=&Accountant[0][1];
    AllBonus[5]=&Accountant[1][0];
    AllBonus[6]=&Accountant[1][1];
    AllBonus[7]=&Accountant[2][0];
    AllBonus[8]=&Accountant[2][1];
    //Welcome Screen
    cout<<"Welcome to HSBC Bank"<<endl;
    cout<<"Select View: "<<endl;
    cout<<"1. Account Holder View "<<endl;
    cout<<"2. Owner View "<<endl;
    cout<<"3. Exit "<<endl;
    while(scanf("%d",&View)==1)
    {
        bool Firstbreak;//bool type variable
        Firstbreak=false;
        fflush(stdin);
        switch(View)//switch statement
        {
            bool Secondbreak;
            Secondbreak=false;
        case 1:
            cout<<"Account Holder View"<<endl;
            cout<<"Select Option"<<endl;
            cout<<"1. Add Normal Account "<<endl;
            cout<<"2. Add LoanTaking Account "<<endl;
            cout<<"3. Normal Account Withdraw "<<endl;
            cout<<"4. LoanTaking Account Withdraw "<<endl;
            cout<<"5. Normal Account Deposit "<<endl;
            cout<<"6. LoanTaking Account Deposit "<<endl;
            cout<<"7. Normal Account Interest "<<endl;
            cout<<"8. LoanTaking Account Interest "<<endl;
            cout<<"9. Normal Account Details"<<endl;
            cout<<"10. LoanTaking Account Details "<<endl;
            cout<<"11. Take Loan "<<endl;
            cout<<"12. Delete Normal Account "<<endl;
            cout<<"13. Delete LoanTaking Account "<<endl;
            cout<<"14. Exit"<<endl;
            int Option;
            while(scanf("%d",&Option)==1)
            {
                Secondbreak=false;
                fflush(stdin);
                switch(Option)
                {
                    bool Shouldbreak;
                    Shouldbreak=false;
                case 1:
                    Account[CountBranch][CountAccount].SetName();
                    Account[CountBranch][CountAccount].SetBalance();
                    cout<<"Your Account has been created"<<endl;
                    Account[CountBranch][CountAccount].ShowName();
                    Account[CountBranch][CountAccount].ShowBalance();
                    Account[CountBranch][CountAccount].ShowAccountID();
                    CountAccount++;
                    if(CountAccount>=ACCOUNT)
                    {
                        CountAccount=0;
                        CountBranch++;
                    }
                    break;
                case 2:
                    LoanTakingAccount[LoanCountBranch][LoanCountAccount].SetName();
                    LoanTakingAccount[LoanCountBranch][LoanCountAccount].SetBalance();
                    cout<<"Your Account has been created"<<endl;
                    LoanTakingAccount[LoanCountBranch][LoanCountAccount].ShowName();
                    LoanTakingAccount[LoanCountBranch][LoanCountAccount].ShowBalance();
                    LoanTakingAccount[LoanCountBranch][LoanCountAccount].ShowAccountID();
                    LoanCountAccount++;
                    if(LoanCountAccount>=ACCOUNT)
                    {
                        LoanCountAccount=0;
                        LoanCountBranch++;
                    }
                    break;
                case 3:
                    Shouldbreak=false;
                    int TempID,AccID;
                    cout<<"Enter Account ID:";
                    cin>>TempID;
                    fflush(stdin);
                    for(i=0;i<BRANCH;i++)
                    {
                        for(j=0;j<ACCOUNT;j++)
                        {
                            AccID=Account[i][j].GetAccountID();
                            if(TempID==AccID)
                            {
                                Account[i][j].ShowName();
                                Account[i][j].ShowBalance();
                                Account[i][j].ShowAccountID();
                                Account[i][j].WithdrawAndUpdate();
                                Shouldbreak=true;
                                break;
                            }
                        }
                        if(Shouldbreak==true)
                            break;

                    }
                    break;
                case 4:
                    Shouldbreak=false;
                    cout<<"Enter Account ID:";
                    cin>>TempID;
                    fflush(stdin);
                    for(i=0;i<BRANCH;i++)
                    {
                        for(j=0;j<ACCOUNT;j++)
                        {
                            AccID=LoanTakingAccount[i][j].GetAccountID();
                            if(TempID==AccID)
                            {
                                LoanTakingAccount[i][j].ShowName();
                                LoanTakingAccount[i][j].ShowBalance();
                                LoanTakingAccount[i][j].ShowAccountID();
                                LoanTakingAccount[i][j].WithdrawAndUpdate();
                                Shouldbreak=true;
                                break;
                            }
                        }
                        if(Shouldbreak==true)
                            break;

                    }
                    break;
                case 5:
                    Shouldbreak=false;
                    cout<<"Enter Account ID:";
                    cin>>TempID;
                    fflush(stdin);
                    for(i=0;i<BRANCH;i++)
                    {
                        for(j=0;j<ACCOUNT;j++)
                        {
                            AccID=Account[i][j].GetAccountID();
                            if(TempID==AccID)
                            {
                                Account[i][j].ShowName();
                                Account[i][j].ShowBalance();
                                Account[i][j].ShowAccountID();
                                Account[i][j].DepositAndUpdate();
                                Shouldbreak=true;
                                break;
                            }
                        }
                        if(Shouldbreak==true)
                            break;
                    }
                    break;
                case 6:
                    Shouldbreak=false;
                    cout<<"Enter Account ID:";
                    cin>>TempID;
                    fflush(stdin);
                    for(i=0;i<BRANCH;i++)
                    {
                        for(j=0;j<ACCOUNT;j++)
                        {
                            AccID=LoanTakingAccount[i][j].GetAccountID();
                            if(TempID==AccID)
                            {
                                LoanTakingAccount[i][j].ShowName();
                                LoanTakingAccount[i][j].ShowBalance();
                                LoanTakingAccount[i][j].ShowAccountID();
                                LoanTakingAccount[i][j].DepositAndUpdate();
                                Shouldbreak=true;
                                break;
                            }
                        }
                        if(Shouldbreak==true)
                            break;

                    }
                    break;
                case 7:
                    Shouldbreak=false;
                    cout<<"Enter Account ID:";
                    cin>>TempID;
                    fflush(stdin);
                    for(i=0;i<BRANCH;i++)
                    {
                        for(j=0;j<ACCOUNT;j++)
                        {
                            AccID=Account[i][j].GetAccountID();
                            if(TempID==AccID)
                            {
                                Account[i][j].ShowName();
                                Account[i][j].ShowBalance();
                                Account[i][j].ShowAccountID();
                                Account[i][j].CalcInterestAndUpdate(2);
                                Account[i][j].ShowBalance();
                                Shouldbreak=true;
                                break;
                            }
                        }
                        if(Shouldbreak==true)
                            break;
                    }
                    break;
                case 8:
                    Shouldbreak=false;
                    cout<<"Enter Account ID:";
                    cin>>TempID;
                    fflush(stdin);
                    for(i=0;i<BRANCH;i++)
                    {
                        for(j=0;j<ACCOUNT;j++)
                        {
                            AccID=LoanTakingAccount[i][j].GetAccountID();
                            cout<<"AccID: "<<AccID;
                            if(TempID==AccID)
                            {
                                LoanTakingAccount[i][j].ShowName();
                                LoanTakingAccount[i][j].ShowBalance();
                                LoanTakingAccount[i][j].ShowAccountID();
                                LoanTakingAccount[i][j].CalcInterestAndUpdate(2);
                                LoanTakingAccount[i][j].ShowBalance();
                                Shouldbreak=true;
                                break;
                            }
                        }
                        if(Shouldbreak==true)
                            break;

                    }
                    break;
                case 9:
                    Shouldbreak=false;
                    cout<<"Enter Account ID:";
                    cin>>TempID;
                    fflush(stdin);
                    for(i=0;i<BRANCH;i++)
                    {
                        for(j=0;j<ACCOUNT;j++)
                        {
                            AccID=Account[i][j].GetAccountID();
                            if(TempID==AccID)
                            {
                                Account[i][j].ShowName();
                                Account[i][j].ShowBalance();
                                Account[i][j].ShowAccountID();
                                Account[i][j].ShowLastWithdraw();
                                Account[i][j].ShowLastDeposit();
                                Shouldbreak=true;
                                break;
                            }
                        }
                        if(Shouldbreak==true)
                            break;
                    }
                    break;
                case 10:
                    Shouldbreak=false;
                    cout<<"Enter Account ID:";
                    cin>>TempID;
                    fflush(stdin);
                    for(i=0;i<BRANCH;i++)
                    {
                        for(j=0;j<ACCOUNT;j++)
                        {
                            AccID=LoanTakingAccount[i][j].GetAccountID();
                            if(TempID==AccID)
                            {
                                LoanTakingAccount[i][j].ShowName();
                                LoanTakingAccount[i][j].ShowBalance();
                                LoanTakingAccount[i][j].ShowAccountID();
                                LoanTakingAccount[i][j].CalcInterestAndUpdate(2);
                                LoanTakingAccount[i][j].ShowBalance();
                                Shouldbreak=true;
                                break;
                            }
                        }
                        if(Shouldbreak==true)
                            break;

                    }
                    break;
                case 11:
                    Shouldbreak=false;
                    cout<<"Enter Account ID:";
                    cin>>TempID;
                    fflush(stdin);
                    for(i=0;i<BRANCH;i++)
                    {
                        for(j=0;j<ACCOUNT;j++)
                        {
                            AccID=LoanTakingAccount[i][j].GetAccountID();
                            if(TempID==AccID)
                            {
                                LoanTakingAccount[i][j].ShowName();
                                LoanTakingAccount[i][j].ShowBalance();
                                LoanTakingAccount[i][j].ShowAccountID();
                                TempBalance=LoanTakingAccount[i][j].GetBalance();
                                LoanTakingAccount[i][j].CalcLoanLimit(TempBalance);
                                LoanTakingAccount[i][j].TakingLoan();
                                LoanTakingAccount[i][j].UpdateLoanBalance();
                                LoanTakingAccount[i][j].ShowBalance();
                                Shouldbreak=true;
                                break;
                            }
                        }
                        if(Shouldbreak==true)
                            break;

                    }
                    break;
                case 12:
                    Shouldbreak=false;
                    cout<<"Enter Account ID:";
                    cin>>TempID;
                    fflush(stdin);
                    for(i=0;i<BRANCH;i++)
                    {
                        for(j=0;j<ACCOUNT;j++)
                        {
                            AccID=Account[i][j].GetAccountID();
                            if(TempID==AccID)
                            {
                                Account[i][j].ShowName();
                                Account[i][j].ShowBalance();
                                Account[i][j].ShowAccountID();
                                Account[i][j].ShowLastWithdraw();
                                Account[i][j].ShowLastDeposit();
                                cout<<"Deleting Account"<<endl;
                                Account[i][j].UpdateBalance(0);
                                Shouldbreak=true;
                                break;
                            }
                        }
                        if(Shouldbreak==true)
                            break;
                    }
                    break;
                case 13:
                    Shouldbreak=false;
                    cout<<"Enter Account ID:";
                    cin>>TempID;
                    fflush(stdin);
                    for(i=0;i<BRANCH;i++)
                    {
                        for(j=0;j<ACCOUNT;j++)
                        {
                            AccID=LoanTakingAccount[i][j].GetAccountID();
                            if(TempID==AccID)
                            {
                                LoanTakingAccount[i][j].ShowName();
                                LoanTakingAccount[i][j].ShowBalance();
                                LoanTakingAccount[i][j].ShowAccountID();
                                LoanTakingAccount[i][j].CalcInterestAndUpdate(2);
                                LoanTakingAccount[i][j].ShowBalance();
                                cout<<"Deleting LoanTakingAccount"<<endl;
                                LoanTakingAccount[i][j].UpdateBalance(0);
                                Shouldbreak=true;
                                break;
                            }
                        }
                        if(Shouldbreak==true)
                            break;

                    }
                    break;

                case 14:
                    Secondbreak=true;
                    break;
                }
                if(Secondbreak==true)
                    break;
            }
            break;
        case 2:
            bool Shouldbreak;
            Shouldbreak=false;
            cout<<"Owner View"<<endl;
            cout<<"Select Option"<<endl;
            cout<<"1. Add Manager"<<endl;
            cout<<"2. Add Accountant"<<endl;
            cout<<"3. Add Office Staff"<<endl;
            cout<<"4. Calculate Manager Bonus"<<endl;
            cout<<"5. Calculate Accountant Bonus"<<endl;
            cout<<"6. See Account Holder Details"<<endl;
            cout<<"7. Calculate Branch Total"<<endl;
            cout<<"8. Show Employee Bonus"<<endl;
            cout<<"9. Add Owner Details"<<endl;
            cout<<"10. Calculate Owner Bonus"<<endl;
            cout<<"11. Exit"<<endl;
            while(scanf("%d",&Option)==1)
            {
                bool Thirdbreak;
                Thirdbreak=false;
                fflush(stdin);
                bool Shouldbreak;
                switch(Option)
                {
                case 1:
                    Manager[CountManager].SetName(CountManager);
                    Manager[CountManager].SetID(CountManager);
                    Manager[CountManager].ShowName(CountManager);
                    Manager[CountManager].ShowID(CountManager);
                    CountManager++;
                    break;
                case 2:
                    Accountant[CountAccountantBranch][CountAccountantNo].SetName(CountAccountantBranch,CountAccountantNo);
                    Accountant[CountAccountantBranch][CountAccountantNo].SetID(CountAccountantBranch,CountAccountantNo);
                    CountAccountantNo++;
                    if(CountAccountantNo>=ACCOUNTANT)
                    {
                        CountAccountantBranch++;
                        CountAccountantNo=0;
                    }
                    break;
                case 3:
                    OfficeStaff[CountStaffBranch][CountStaffNo].SetName(CountStaffBranch,CountStaffNo);
                    OfficeStaff[CountStaffBranch][CountStaffNo].SetID(CountStaffBranch,CountStaffNo);
                    CountStaffNo++;
                    if(CountStaffNo>=STAFF)
                    {
                        CountStaffBranch++;
                        CountStaffNo=0;
                    }
                    break;
                case 4:
                    int TempID,AccID;
                    cout<<"Enter Manager ID:";
                    cin>>TempID;
                    fflush(stdin);
                    for(i=0;i<BRANCH;i++)
                    {
                        AccID=Manager[i].GetID();
                        if(TempID==AccID)
                        {
                            int Start, End, Bonus;
                            cout<<"Enter Start Account Number: ";
                            cin>>Start;
                            fflush(stdin);
                            cout<<"Enter End Account Number: ";
                            cin>>End;
                            fflush(stdin);
                            cout<<"Enter Bonus Perchantage: ";
                            cin>>Bonus;
                            fflush(stdin);
                            cout<<"Calculating Manager Bonus"<<endl;
                            Manager[i].CalcBonus(Account, i, Start, End, Bonus);
                            Manager[i].ShowBonus(i);
                            break;
                        }
                    }
                    break;
                case 5:
                    Shouldbreak=false;
                    cout<<"Enter Accountant ID:";
                    cin>>TempID;
                    fflush(stdin);
                    for(i=0;i<BRANCH;i++)
                    {
                        for(j=0;j<ACCOUNT;j++)
                        {
                            AccID=Accountant[i][j].GetID();
                            if(TempID==AccID)
                            {
                                int Start, End, Bonus;
                                cout<<"Enter Start Account Number: ";
                                cin>>Start;
                                fflush(stdin);
                                cout<<"Enter End Account Number: ";
                                cin>>End;
                                fflush(stdin);
                                cout<<"Enter Bonus Percentage: ";
                                cin>>Bonus;
                                fflush(stdin);
                                cout<<"Calculating Accountant Bonus"<<endl;
                                Accountant[i][j].CalcBonus(Account, i, Start, End, Bonus);
                                Accountant[i][j].ShowBonus(i,j);
                                Shouldbreak=true;
                                break;
                            }
                        }
                        if(Shouldbreak==true)
                            break;
                    }
                    break;
                case 6:
                    cout<<Account;
                    cout<<LoanTakingAccount;
                    break;
                case 7:
                    int Start,End,branch;
                    cout<<"Enter the Branch Number: ";
                    cin>>branch;
                    fflush(stdin);
                    cout<<"Enter Start Account Number: ";
                    cin>>Start;
                    fflush(stdin);
                    cout<<"Enter End Account Number: ";
                    cin>>End;
                    Branch[branch-1].CalcBranchTotal(Account, branch-1, Start, End);
                    Branch[branch-1].ShowBranchTotal(branch-1);
                    break;
                case 8:
                    int i;
                    for(i=0;i<EMPLOYEE;i++)
                    {
                        if(AllBonus[i]->GetBonus()!=0)
                        {
                            AllBonus[i]->ShowBonus();
                        }
                    }
                    break;
                case 9:
                    Owner.SetName();
                    Owner.SetID();
                    Owner.ShowName();
                    Owner.ShowID();
                    break;
                case 10:
                    int bonus;
                    cout<<"Enter Bonus Percentage:  ";
                    cin>>bonus;
                    fflush(stdin);
                    Owner.CalcBonus(Account, bonus);
                    Owner.ShowBonus();
                    break;
                case 11:
                    Thirdbreak=true;
                    break;
                }
                if(Thirdbreak==true)
                    break;

            }
            break;
        case 3:
            Firstbreak=true;
            break;
        }
        if(Firstbreak==true)
            break;
    }
    getchar();
    return 0;
}
