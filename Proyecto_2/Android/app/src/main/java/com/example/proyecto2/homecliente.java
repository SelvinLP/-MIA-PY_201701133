package com.example.proyecto2;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Color;
import android.os.Bundle;
import android.util.Log;
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

public class homecliente extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_homecliente);

        agregarFilaTabla();
    }

    private RequestQueue mQueue;
    public void agregarFilaTabla() {
        mQueue= Volley.newRequestQueue(this);
        JSONArray jsonArray;
        //Obtener Usuarios
        String url="http://192.168.0.9:3000/getProducto";
        JsonArrayRequest getrequest=new JsonArrayRequest(Request.Method.GET, url, null, new Response.Listener<JSONArray>() {
            @Override
            public void onResponse(JSONArray response) {
                for(int i=0;i<response.length();i++){
                    try {
                        JSONObject producto = response.getJSONObject(i);
                        if(producto.getString("Descripcion").equals("Eliminado")){

                        }else{
                            LlenarTabla(producto.getString("Descripcion"),producto.getString("Id_Categoria"),producto.getString("Precio"));
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

    public void LlenarTabla(String Nombre, final String Categoria, String Precio){
        TableLayout table = findViewById(R.id.tableLayout1);
        TableRow tableRow = new TableRow(this);
        table.addView(tableRow);
        TextView textView = new TextView(this);
        textView.setBackgroundColor(Color.parseColor("#FFFFFF"));
        textView.setText(Nombre);
        final TextView textView2 = new TextView(this);

        mQueue= Volley.newRequestQueue(this);
        JSONArray jsonArray;
        //Obtener Usuarios
        String url="http://192.168.0.9:3000/getCategoria";
        JsonArrayRequest getrequest=new JsonArrayRequest(Request.Method.GET, url, null, new Response.Listener<JSONArray>() {
            @Override
            public void onResponse(JSONArray response) {
                for(int i=0;i<response.length();i++){
                    try {
                        JSONObject producto = response.getJSONObject(i);
                        if(producto.getString("Id_Categoria").equals(Categoria)){
                            textView2.setText(producto.getString("Nombre"));
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

        textView2.setBackgroundColor(Color.parseColor("#FFFFFF"));
        TextView textView3 = new TextView(this);
        textView3.setText(Precio);
        textView3.setBackgroundColor(Color.parseColor("#FFFFFF"));

        tableRow.addView(textView);
        tableRow.addView(textView2);
        tableRow.addView(textView3);
        ;
    }
}
