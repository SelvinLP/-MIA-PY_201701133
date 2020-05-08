package com.example.proyecto2;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.CoreComponentFactory;

import android.app.Activity;
import android.content.Intent;
import android.content.res.Resources;
import android.graphics.Color;
import android.os.Bundle;
import android.util.Log;
import android.view.Gravity;
import android.view.View;
import android.widget.LinearLayout;
import android.widget.TableLayout;
import android.widget.TableRow;
import android.widget.TextView;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.JsonArrayRequest;
import com.android.volley.toolbox.Volley;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;

import static android.graphics.Color.parseColor;

public class homeadmin extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_homeadmin);

        agregarFilaTabla();

        findViewById(R.id.button).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent (v.getContext(), CrudUsuario.class);
                startActivityForResult(intent, 0);
            }
        });
    }

    private RequestQueue mQueue;
    public void agregarFilaTabla() {
        mQueue= Volley.newRequestQueue(this);
        JSONArray jsonArray;
        //Obtener Usuarios
        String url="http://192.168.0.9:3000/getUsers";
        JsonArrayRequest getrequest=new JsonArrayRequest(Request.Method.GET, url, null, new Response.Listener<JSONArray>() {
            @Override
            public void onResponse(JSONArray response) {
                for(int i=0;i<response.length();i++){
                    try {
                        JSONObject usu = response.getJSONObject(i);
                        if(usu.getString("Estado").equals("Eliminado")) {
                        }else{
                            LlenarTabla(usu.getString("Nombre"),usu.getString("Correo"),usu.getString("FK_Rol"));
                        }
                    } catch (JSONException e) {
                        e.printStackTrace();
                    }
                }
            }
        }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                Log.d("Hubo un error", error.toString());
            }
        });
        mQueue.add(getrequest);

    }

    public void LlenarTabla(String Nombre,String Correo,String Rol){
        TableLayout table = findViewById(R.id.tableLayout1);
        TableRow tableRow = new TableRow(this);
        table.addView(tableRow);
        TextView textView = new TextView(this);
        textView.setBackgroundColor(Color.parseColor("#FFFFFF"));
        textView.setText(Nombre);
        TextView textView2 = new TextView(this);
        textView2.setText(Correo);
        textView2.setBackgroundColor(Color.parseColor("#FFFFFF"));
        TextView textView3 = new TextView(this);
        if(Rol.equals("1")){
            textView3.setText("Admin");
        }else if(Rol.equals("2")){
            textView3.setText("Servicio de Ayuda");
        }else if(Rol.equals("3")){
            textView3.setText("Cliente");
        }
        textView3.setBackgroundColor(Color.parseColor("#FFFFFF"));

        tableRow.addView(textView);
        tableRow.addView(textView2);
        tableRow.addView(textView3);
;
    }
}
