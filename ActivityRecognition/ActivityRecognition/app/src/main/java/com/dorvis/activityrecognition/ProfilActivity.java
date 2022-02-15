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
import android.widget.Toast;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class ProfilActivity extends AppCompatActivity {
    private TextView profileShowEmail;
    private TextView profileShowBirthday;
    private TextView profileShowHeight;
    private TextView profileShowWeight;
    private Button modifyButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.INTERNET}, PackageManager.PERMISSION_GRANTED);

        //Remove title bar
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getSupportActionBar().hide();

        setContentView(R.layout.activity_profil);

        profileShowEmail = findViewById(R.id.updateEmailBox);
        profileShowEmail.setText(CurrentPerson.INSTANCE.getPerson().getEmail());

        profileShowBirthday = findViewById(R.id.updateBirthBox);
        profileShowBirthday.setText(CurrentPerson.INSTANCE.getPerson().getBirthday());

        profileShowHeight = findViewById(R.id.updateHeightBox);
        profileShowHeight.setText(CurrentPerson.INSTANCE.getPerson().getHeight().toString());

        profileShowWeight = findViewById(R.id.updateWeightBox);
        profileShowWeight.setText(CurrentPerson.INSTANCE.getPerson().getWeight().toString());

        modifyButton = (Button) findViewById(R.id.updateButton);
        modifyButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try {
                    updateUserProfile();
                } catch (SQLException throwables) {
                    throwables.printStackTrace();
                }
            }
        });
    }

    public void updateUserProfile() throws SQLException {
        if (profileShowBirthday.getText().toString().equals("") || profileShowWeight.getText().toString().equals("") || profileShowHeight.getText().toString().equals("")) {
            Toast.makeText(getApplicationContext(), "All fields must be completed",
                    Toast.LENGTH_SHORT).show();
            return;
        }

        SQLConnection sqlConnection = new SQLConnection();
        Connection connection = sqlConnection.getConnection();

        PreparedStatement preparedStatement = connection.prepareStatement("UPDATE [ActivityRecognitionDB].[dbo].[User] SET birthday = ?, height = ?, weight = ? WHERE email = ?");

        preparedStatement.setString(1, profileShowBirthday.getText().toString());
        preparedStatement.setString(2, profileShowHeight.getText().toString());
        preparedStatement.setString(3, profileShowWeight.getText().toString());
        preparedStatement.setString(4, profileShowEmail.getText().toString());

        CurrentPerson.INSTANCE.getPerson().setBirthday(profileShowBirthday.getText().toString());
        CurrentPerson.INSTANCE.getPerson().setWeight(Double.parseDouble(profileShowWeight.getText().toString()));
        CurrentPerson.INSTANCE.getPerson().setHeight(Double.parseDouble(profileShowHeight.getText().toString()));

        Toast.makeText(getApplicationContext(), "Modify success!",
                Toast.LENGTH_SHORT).show();

        preparedStatement.executeQuery();

        connection.close();
    }
}
