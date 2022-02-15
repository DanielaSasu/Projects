package com.dorvis.activityrecognition;

import com.google.android.gms.location.DetectedActivity;

public class Person {
    private int idPerson;
    private String email;
    private String password;
    private String birthday;
    private Double height;
    private Double weight;

    public int getNrDriving() {
        return nrDriving;
    }

    public int getNrCycling() {
        return nrCycling;
    }

    public int getNrStanding() {
        return nrStanding;
    }

    public int getNrRunning() {
        return nrRunning;
    }

    public int getNrStill() {
        return nrStill;
    }

    public int getNrTitling() {
        return nrTitling;
    }

    public int getNrWalking() {
        return nrWalking;
    }

    private int nrDriving;
    private int nrCycling;
    private int nrStanding;
    private int nrRunning;
    private int nrStill;
    private int nrTitling;
    private int nrWalking;

    public Person(String email, String password, String birthday, Double height, Double weight) {
        this.email = email;
        this.password = password;
        this.birthday = birthday;
        this.height = height;
        this.weight = weight;

        this.nrDriving = 0;
        this.nrCycling = 0;
        this.nrStanding = 0;
        this.nrRunning = 0;
        this.nrStill = 0;
        this.nrTitling = 0;
        this.nrWalking = 0;
    }

    public int getIdPerson() {
        return idPerson;
    }

    public void setIdPerson(int idPerson) {
        this.idPerson = idPerson;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public String getBirthday() {
        return birthday;
    }

    public void setBirthday(String birthday) {
        this.birthday = birthday;
    }

    public Double getHeight() {
        return height;
    }

    public void setHeight(Double height) {
        this.height = height;
    }

    public Double getWeight() {
        return weight;
    }

    public void setWeight(Double weight) {
        this.weight = weight;
    }

    public void resetActivityNumber(){
        this.nrDriving = 0;
        this.nrCycling = 0;
        this.nrStanding = 0;
        this.nrRunning = 0;
        this.nrStill = 0;
        this.nrTitling = 0;
        this.nrWalking = 0;
    }


    public void increaseActivityNr(int type) {
        switch (type) {
            case DetectedActivity.IN_VEHICLE: {
                nrDriving++;
                break;
            }
            case DetectedActivity.ON_BICYCLE: {
                nrCycling++;
               break;
            }
            case DetectedActivity.ON_FOOT: {
                nrStanding++;
                break;
            }
            case DetectedActivity.RUNNING: {
                nrRunning++;
                break;
            }
            case DetectedActivity.STILL: {
                nrStill++;
                break;
            }
            case DetectedActivity.TILTING: {
                nrTitling++;
                break;
            }
            case DetectedActivity.WALKING: {
                nrWalking++;
                break;
            }
        }
    }
}
