package com.company;

public class CurrentAccount extends Account{
    private double overdraftLimit;

    public CurrentAccount(int accountNumber,double overdraftLimit) {
        super(accountNumber);
        this.overdraftLimit = overdraftLimit;
    }

    @Override
    public String toString() {
        return "Current account " + getAccountNumber() + ": " + "balance = " + getBalance();
    }

    @Override
    public void deposit(double sum)
    {
        if (sum>0)
            super.deposit(sum);
        else
            System.err.println("CurrentAccount.deposit(...): "
                    +"cannot deposit negative amount.");
    }
    @Override
    public void withdraw(double sum)
    {
        if (sum>0)
            super.withdraw(sum);
        else
            System.err.println("CurrentAccount.withdraw(...): " + "cannot withdraw negative amount.");
    }
}
