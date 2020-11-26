package com.company;

public class SavingsAccount extends Account{
    private double interest;


    public SavingsAccount(int accountNumber,double interest) {
        super(accountNumber);
        this.interest = interest;
    }
    public void InterestBalance(){
        deposit((getBalance()*interest)/100 + getBalance());
    }

    @Override
    public String toString() {
        return "Savings account " + getAccountNumber() + ": " + "balance = " + getBalance();
    }
    @Override
    public void deposit(double sum)
    {
        if (sum>0)
            super.deposit(sum);
        else
            System.err.println("SavingAccount.deposit(...): "
                    +"cannot deposit negative amount.");
    }
    @Override
    public void withdraw(double sum)
    {
        if (sum>0)
            super.withdraw(sum);
        else
            System.err.println("SavingAccount.withdraw(...): " + "cannot withdraw negative amount.");
    }
}
