package theedg.es.drops;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.view.View;
import android.widget.ToggleButton;

public class MainActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

    public void onSyncToggleClicked(View view) {
        // Check if the toggle button is on.
        ToggleButton button = (ToggleButton) view;
        boolean on = button.isChecked();

        if (on) {
            // turn sync on
        } else {
            // turn sync off
        }
    }

}
