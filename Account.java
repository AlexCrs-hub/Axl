package com.company;

public class Account
{
    private double balance; //The current balance
    private int accountNumber; //The account number
    public Account(int accountNumber)
    {
        balance=0.0;
        this.accountNumber=accountNumber;
    }
    public void deposit(double sum)
    {
        if (sum>0)
            balance+=sum;
        else
            System.err.println("Account.deposit(...): "
                    +"cannot deposit negative amount.");
    }
    public void withdraw(double sum)
    {
        if (sum>0)
            balance-=sum;
        else
            System.err.println("Account.withdraw(...): " + "cannot withdraw negative amount.");
    }
    public double getBalance()
    {
        return balance;
    }
    public double getAccountNumber()
    {
        return accountNumber;
    }
    public String toString()
    {
        return "Acc " + accountNumber + ": " + "balance = " + balance;
    }
    public final void print()
    {
//Don't override this,
//override the toString method
        System.out.println( toString() );
    }
}
