package com.dorvis.activityrecognition;


import android.annotation.SuppressLint;
import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.view.Window;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class RegisterActivity extends AppCompatActivity {

    private Button saveButton;
    private EditText registerEmail;
    private EditText registerPasssword;
    private EditText registerBirthdate;
    private EditText registerWeight;
    private EditText registerHeight;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getSupportActionBar().hide();

        setContentView(R.layout.activity_register);


        saveButton = findViewById(R.id.registerButton);
        saveButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try {
                    registerUser();
                } catch (SQLException throwables) {
                    throwables.printStackTrace();
                }
            }
        });
    }

    @SuppressLint("SetTextI18n")
    public void registerUser() throws SQLException {

        registerEmail = (EditText) findViewById((R.id.registerEmailBox));
        registerPasssword = (EditText) findViewById((R.id.registerPasswordBox));
        registerBirthdate = (EditText) findViewById((R.id.birthBox));
        registerWeight = (EditText) findViewById((R.id.weightBox));
        registerHeight = (EditText) findViewById((R.id.heightBox));

        if (registerEmail.getText().toString().equals("") || registerPasssword.getText().toString().equals("") || registerBirthdate.getText().toString().equals("") ||
                registerWeight.getText().toString().equals("") || registerHeight.getText().toString().equals("")) {
            Toast.makeText(getApplicationContext(), "All fields must be completed",
                    Toast.LENGTH_SHORT).show();
            return;
        }

        SQLConnection sqlConnection = new SQLConnection();
        Connection connection = sqlConnection.getConnection();

        PreparedStatement preparedStatement = connection.prepareStatement("INSERT INTO [ActivityRecognitionDB].[dbo].[User] (email, password,birthday,weight,height)" + "values (?,?,?,?,?)");

        preparedStatement.setString(1, registerEmail.getText().toString());
        preparedStatement.setString(2, registerPasssword.getText().toString());
        preparedStatement.setString(3, registerBirthdate.getText().toString());
        preparedStatement.setString(4, registerWeight.getText().toString());
        preparedStatement.setString(5, registerHeight.getText().toString());

        CurrentPerson.INSTANCE.setPerson(new Person(registerEmail.getText().toString(), registerPasssword.getText().toString(),
                registerBirthdate.getText().toString(), Double.parseDouble(registerWeight.getText().toString()), Double.parseDouble(registerHeight.getText().toString())));

        Toast.makeText(getApplicationContext(), "Register success!",
                Toast.LENGTH_SHORT).show();

        Intent intent = new Intent(this, MenuActivity.class);
        startActivity(intent);

        preparedStatement.executeQuery();

        connection.close();
    }
}