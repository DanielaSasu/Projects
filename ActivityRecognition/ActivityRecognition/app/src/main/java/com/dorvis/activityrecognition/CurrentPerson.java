package com.dorvis.activityrecognition;

public enum CurrentPerson {
    INSTANCE;
    private Person person=null;

    public Person getPerson() {
        return person;
    }

    public void setPerson(Person person) {
        this.person = person;
    }
}
