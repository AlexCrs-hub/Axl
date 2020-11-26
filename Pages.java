package com.company;

public class Pages {
    private String name;
    private String domainOfActivity;
    private String description;
    private User admin;

    public Pages(String name, String domainOfActivity, String description, User admin) {
        this.name = name;
        this.domainOfActivity = domainOfActivity;
        this.description = description;
        this.admin = admin;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {

        this.name = name;
    }

    public String getDomainOfActivity() {

        return domainOfActivity;
    }

    public void setDomainOfActivity(String domainOfActivity) {

        this.domainOfActivity = domainOfActivity;
    }

    public String getDescription() {

        return description;
    }

    public void setDescription(String description) {

        this.description = description;
    }

    public User getAdmin() {
        return admin;
    }

    public void setAdmin(User admin) {

        this.admin = admin;
    }
}
