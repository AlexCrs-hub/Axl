package com.company;

public class Main {

    public static void main(String[] args) {

        User user01 = new User("jablinski@gmail.com", "beastmaster64", "Jack Black","single");
        User user02 = new User("bard@gmail.com", "leagueironforever", "Bard Wonder","married");
        User user03 = new User("JohnMikey@gmail.com", "NotTheBestPassword","John Mike", "single");
        User user04 = new User("Mando@gmail.com", "NoDroidsPls","Pedro Mando","single");
        User user05 = new User("ObiJuan@gmail.com", "GeneralOfForce","Obi Juan Genobi","In a relationship");
        User user06 = new User("Felix@yahoo.com", "RickRolling","Felik Kjeweds", "married");
        User user07 = new User("Steve@gmail.com", "JustSteveNGL*34","Steve Beave","single");
        User user08 = new User("BorisVladmiri@gmail.com", "password1234","Boris Stanin","single");

        user01.addFriend(user02);
        user01.addFriend(user05);
        user01.addFriend(user06);
        user01.addFriend(user07);
        user02.addFriend(user01);
        user02.addFriend(user03);
        user02.addFriend(user06);
        user03.addFriend(user01);
        user03.addFriend(user02);
        user04.addFriend(user01);
        user04.addFriend(user02);
        user04.addFriend(user07);
        user05.addFriend(user06);
        user06.addFriend(user01);
        user06.addFriend(user04);
        user07.addFriend(user03);
        user08.addFriend(user06);
        user08.addFriend(user01);

        Pages page01 = new Pages("Berrics", "sport", "mindblowing skateboarding", user04);
        Pages page02 = new Pages("RedBull", "sport", "if it is extreme it is here", user01);
        Pages page03 = new Pages("CursedMemes", "entertainment", "cursed images for cursed minds", user07);
        Pages page04 = new Pages("Antena3", "politics", "Mircea Badea fighting", user03);
        Pages page05 = new Pages("9gag", "education", "educating people", user06);
        Pages page06 = new Pages("Marvel", "entertainment", "comics and movies", user05);
        Pages page07 = new Pages("Emerica", "clothing", "rad shoes", user02);
        Pages page08 = new Pages("MoneyWeTakeMoney","economy","we take your money", user08);

        user01.likePage(page01);
        user01.likePage(page04);
        user01.likePage(page08);
        user02.likePage(page05);
        user03.likePage(page02);
        user06.likePage(page06);
        user04.likePage(page07);
        user05.likePage(page03);
        user07.likePage(page03);
        user08.likePage(page01);

        //ex 1
        for(User user: user01.getFriends()){
            if(user.getStatus().equals("single")){
                System.out.println(user.getUsername());
            }
        }

        //ex 2
        for(int i = 0; i < user01.getPages().size();++i){
            Pages pages = user01.getPages().get(i);
            if(pages.getDomainOfActivity().equals("politics")) {
                user01.dislikePage(pages);
            }
            else if(pages.getDomainOfActivity().equals("sport")){
                user01.dislikePage(pages);
            }
        }

        for(int i = 0; i < user01.getPages().size();++i){
            System.out.println(user01.getPages().get(i).getName());
        }

        //ex 3


    }
}
