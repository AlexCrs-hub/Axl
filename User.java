package com.company;

import java.util.ArrayList;

public class User {
    private String username;
    private String password;
    private String fullName;
    private ArrayList<User> friends = new ArrayList<>();
    private ArrayList<Pages> pages = new ArrayList<>();
    private String status;

    public User(String username, String password, String fullName, String status) {
        this.username = username;
        this.password = password;
        this.fullName = fullName;
        this.status = status;
    }

    public String getFullName() {
        return fullName;
    }

    public void setFullName(String fullName) {
        this.fullName = fullName;
    }

    public String getUsername() {

        return username;
    }

    public void setUsername(String username) {

        this.username = username;
    }

    public String getPassword() {

        return password;
    }

    public void setPassword(String password) {

        this.password = password;
    }

    public ArrayList<User> getFriends() {

        return friends;
    }

    public void setFriends(ArrayList<User> friends) {

        this.friends = friends;
    }

    public ArrayList<Pages> getPages() {

        return pages;
    }

    public void setPages(ArrayList<Pages> pages) {

        this.pages = pages;
    }

    public String getStatus() {

        return status;
    }

    public void setStatus(String status) {

        this.status = status;
    }

    public void addFriend(User user){

        friends.add(user);
    }

    public void likePage(Pages page){

        pages.add(page);
    }

    public void dislikePage(Pages page){

        pages.remove(page);
    }
}
