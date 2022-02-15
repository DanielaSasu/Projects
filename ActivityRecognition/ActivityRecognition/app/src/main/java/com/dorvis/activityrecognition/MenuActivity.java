package com.dorvis.activityrecognition;

import android.Manifest;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.support.v4.app.ActivityCompat;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.view.Window;
import android.widget.Button;
import android.widget.TextView;

import java.sql.SQLException;

public class MenuActivity extends AppCompatActivity {
    private Button buttonProfile;
    private Button buttonCurrentActivity;
    private Button buttonAllActivities;
    private Button buttonPopularActivity;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.INTERNET}, PackageManager.PERMISSION_GRANTED);

        //Remove title bar
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getSupportActionBar().hide();

        setContentView(R.layout.activity_menu);

        buttonProfile = (Button) findViewById(R.id.buttonProfile);
        buttonProfile.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                openProfilActivity();
            }
        });

        buttonCurrentActivity = (Button) findViewById(R.id.buttonCurrentActivity);
        buttonCurrentActivity.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                openCurrentActivity();
            }
        });

        buttonAllActivities = (Button) findViewById(R.id.buttonAll);
        buttonAllActivities.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                openAllActivities();
            }
        });

        buttonPopularActivity = (Button) findViewById(R.id.buttonPopularActivity);
        buttonPopularActivity.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                openPopularActivities();
            }
        });
    }
    public void openProfilActivity() {
        Intent intent = new Intent(this, ProfilActivity.class);
        startActivity(intent);
    }

    public void openCurrentActivity() {
        Intent intent = new Intent(this, SecondActivity.class);
        startActivity(intent);
    }

    public void openAllActivities() {
        Intent intent = new Intent(this, AllActivity.class);
        startActivity(intent);
    }

    public void openPopularActivities() {
        Intent intent = new Intent(this, PopularActivity.class);
        startActivity(intent);
    }
}
