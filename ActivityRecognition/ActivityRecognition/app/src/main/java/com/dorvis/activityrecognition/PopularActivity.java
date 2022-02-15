package com.dorvis.activityrecognition;

import android.Manifest;
import android.app.Activity;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.support.v4.app.ActivityCompat;
import android.support.v7.app.AppCompatActivity;
import android.view.Window;
import android.widget.ImageView;
import android.widget.TextView;

public class PopularActivity extends AppCompatActivity {
    private ImageView imgActivity;
    private TextView txtActivity;
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.INTERNET}, PackageManager.PERMISSION_GRANTED);

        //Remove title bar
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getSupportActionBar().hide();

        setContentView(R.layout.acivity_popular);

        imgActivity = findViewById(R.id.img_activity_popular);
        txtActivity=findViewById(R.id.textActivity);

        String message;
        int maxim = -1;
        if(CurrentPerson.INSTANCE.getPerson().getNrDriving()>maxim){
            maxim=CurrentPerson.INSTANCE.getPerson().getNrDriving();
            imgActivity.setImageResource(R.drawable.ic_driving);
            txtActivity.setText("Your favorite activity is:\n" + "Driving");
        }
        if(CurrentPerson.INSTANCE.getPerson().getNrCycling()>maxim){
            maxim=CurrentPerson.INSTANCE.getPerson().getNrCycling();
            imgActivity.setImageResource(R.drawable.ic_on_bicycle);
            txtActivity.setText("Your favorite activity is:\n" +"Cycling");
        }
        if(CurrentPerson.INSTANCE.getPerson().getNrRunning()>maxim){
            maxim=CurrentPerson.INSTANCE.getPerson().getNrRunning();
            imgActivity.setImageResource(R.drawable.ic_running);
            txtActivity.setText("Your favorite activity is:\n"+"Running");
        }
        if(CurrentPerson.INSTANCE.getPerson().getNrStill()>maxim){
            maxim=CurrentPerson.INSTANCE.getPerson().getNrStill();
            imgActivity.setImageResource(R.drawable.ic_still);
            txtActivity.setText("Your favorite activity is:\n" +"Still");
        }
        if(CurrentPerson.INSTANCE.getPerson().getNrStanding()>maxim){
            maxim=CurrentPerson.INSTANCE.getPerson().getNrStanding();
            imgActivity.setImageResource(R.drawable.ic_still);
            txtActivity.setText("Your favorite activity is:\n" +"Standing");
        }
        if(CurrentPerson.INSTANCE.getPerson().getNrWalking()>maxim){
            maxim=CurrentPerson.INSTANCE.getPerson().getNrWalking();
            imgActivity.setImageResource(R.drawable.ic_walking);
            txtActivity.setText("Your favorite activity is:\n" +"Walking");
        }
        if(CurrentPerson.INSTANCE.getPerson().getNrTitling()>maxim){
            maxim=CurrentPerson.INSTANCE.getPerson().getNrTitling();
            imgActivity.setImageResource(R.drawable.ic_tilting);
            txtActivity.setText("Your favorite activity is:\n" +"Tilting");
        }

    }
}
