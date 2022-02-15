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
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import java.sql.CallableStatement;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class MainActivity extends AppCompatActivity {
    private Button button;
    private TextView textView;
    private EditText inputEmail;
    private EditText inputPassword;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.INTERNET}, PackageManager.PERMISSION_GRANTED);

        //Remove title bar
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getSupportActionBar().hide();

        setContentView(R.layout.activity_main);

        //Functionality on login button
        button = (Button) findViewById(R.id.loginButton);
        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try {
                    openSecondActivity();
                } catch (SQLException throwables) {
                    throwables.printStackTrace();
                }
            }
        });

        //Functionality on text for register page
        textView = (TextView) findViewById((R.id.registerText));
        textView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                openRegisterActivity();
            }
        });

    }

    public void openSecondActivity() throws SQLException {
        inputEmail = (EditText) findViewById((R.id.emailBox));
        inputPassword = (EditText) findViewById((R.id.passwordBox));

        SQLConnection sqlConnection = new SQLConnection();
        Connection connection = sqlConnection.getConnection();

        if(inputEmail.getText().toString().equals("")||inputPassword.getText().toString().equals("")){
            Toast.makeText(getApplicationContext(), "All fields must be completed",
                    Toast.LENGTH_SHORT).show();
            return;
        }
        if (connection == null) {
            Toast.makeText(getApplicationContext(), "Connection is null",
                    Toast.LENGTH_SHORT).show();
            return;
        }

        try {
            CallableStatement cStmt = connection.prepareCall("{call GetUsers}");
            ResultSet resultSet = cStmt.executeQuery();
            while (resultSet.next()) {
                if (resultSet.getString(2).equals(inputEmail.getText().toString()) &&
                        resultSet.getString(3).equals(inputPassword.getText().toString())) {
                    CurrentPerson.INSTANCE.setPerson(new Person(resultSet.getString(2), resultSet.getString(3),
                            resultSet.getString(4),resultSet.getDouble(5), resultSet.getDouble(6)));
                    Intent intent = new Intent(this, MenuActivity.class);
                    startActivity(intent);
                    connection.close();
                    return;
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        Toast.makeText(getApplicationContext(), "User was not found!",
                Toast.LENGTH_SHORT).show();
        connection.close();
    }


    public void openRegisterActivity() {
        Intent intent = new Intent(this, RegisterActivity.class);
        startActivity(intent);
    }
}