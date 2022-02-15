package com.dorvis.activityrecognition;

import android.Manifest;
import android.app.Activity;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.support.v4.app.ActivityCompat;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.view.Window;
import android.widget.Button;
import android.widget.TextView;

import java.sql.SQLException;

public class AllActivity extends AppCompatActivity {
    private TextView messageDriving;
    private TextView messageCycling;
    private TextView messageTitling;
    private TextView messageStanding;
    private TextView messageRunning;
    private TextView messageWalking;
    private TextView messageStill;
    private Button resetButton;

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.INTERNET}, PackageManager.PERMISSION_GRANTED);

        //Remove title bar
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getSupportActionBar().hide();

        setContentView(R.layout.activity_all);

        messageDriving = findViewById(R.id.textDriving);
        messageCycling = findViewById(R.id.textCycling);
        messageTitling = findViewById(R.id.textTilting);
        messageStanding = findViewById(R.id.textStanding);
        messageRunning = findViewById(R.id.textRunning);
        messageWalking = findViewById(R.id.textWalking);
        messageStill = findViewById(R.id.textStill);
        resetButton=(Button) findViewById(R.id.resetButton);

        resetButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try {
                    reset();
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });

        messageDriving.setText("Driving: " + (String.valueOf(CurrentPerson.INSTANCE.getPerson().getNrDriving())) + " times");
        messageCycling.setText("Cycling: " + (String.valueOf(CurrentPerson.INSTANCE.getPerson().getNrCycling())) + " times");
        messageTitling.setText("Tilting: " + (String.valueOf(CurrentPerson.INSTANCE.getPerson().getNrTitling())) + " times");
        messageStanding.setText("Standing: " + (String.valueOf(CurrentPerson.INSTANCE.getPerson().getNrStanding())) + " times");
        messageRunning.setText("Running: " + (String.valueOf(CurrentPerson.INSTANCE.getPerson().getNrRunning())) + " times");
        messageWalking.setText("Walking: " + (String.valueOf(CurrentPerson.INSTANCE.getPerson().getNrWalking())) + " times");
        messageStill.setText("Still: " + (String.valueOf(CurrentPerson.INSTANCE.getPerson().getNrStill())) + " times");
    }
    public void reset(){
        CurrentPerson.INSTANCE.getPerson().resetActivityNumber();
        messageDriving.setText("Driving: 0 times");
        messageCycling.setText("Cycling: 0 times");
        messageTitling.setText("Tilting: 0 times");
        messageStanding.setText("Standing: 0 times");
        messageRunning.setText("Running: 0 times");
        messageWalking.setText("Walking: 0 times");
        messageStill.setText("Still: 0 times");
    }
}
