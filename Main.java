package com.company;

public class Main {

    public static void main(String[] args) {
	Account acc1 = new Account(12);
       acc1.deposit(789.56);
       acc1.withdraw(81.68);
        //System.out.println(acc1.getBalance());
        acc1.print();

        SavingsAccount sacc1 = new SavingsAccount(11,7.5);
        sacc1.deposit(77.12);
        System.out.println("Current account balance:");
        System.out.println(sacc1.getBalance());
        sacc1.InterestBalance();
        System.out.println("Account after added interest:");
        System.out.println(sacc1.getBalance());
        sacc1.print();

        sacc1.deposit(-5);
        sacc1.withdraw(-6);
    }
}
