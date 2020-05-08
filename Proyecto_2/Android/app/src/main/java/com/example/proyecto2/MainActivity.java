package com.example.proyecto2;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.content.Intent;

import com.android.volley.AuthFailureError;
import com.android.volley.NetworkResponse;
import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.VolleyLog;
import com.android.volley.toolbox.HttpHeaderParser;
import com.android.volley.toolbox.JsonArrayRequest;
import com.android.volley.toolbox.StringRequest;
import com.android.volley.toolbox.Volley;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.UnsupportedEncodingException;

public class MainActivity extends AppCompatActivity {
    private RequestQueue mQueue;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


        //Eventos
        findViewById(R.id.Login).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                MT_IniciarSesion();
            }
        });

        findViewById(R.id.Registrar).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent (v.getContext(), registro.class);
                startActivityForResult(intent, 0);
            }
        });

        findViewById(R.id.RecuperarPass).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                MT_RecuperarContraseña();
            }
        });
    }

    private void MT_RecuperarContraseña() {
        //Datos
        final EditText emailEdit = findViewById(R.id.CampoCorreo);

        String url = "http://192.168.0.9:3000/SendmailRecuperacion";

        mQueue= Volley.newRequestQueue(this);
        JSONObject jsonBodyObj = new JSONObject();
        try{
            jsonBodyObj.put("contraseña","Pass_100");
            jsonBodyObj.put("correo",emailEdit.getText().toString());
        }catch (JSONException e){
            e.printStackTrace();
        }

        final String mRequestBody = jsonBodyObj.toString();

        StringRequest stringRequest = new StringRequest(Request.Method.POST, url, new Response.Listener<String>() {
            @Override
            public void onResponse(String response) {
                Log.i("LOG_RESPONSE", response);
            }
        }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                Log.e("LOG_RESPONSE", error.toString());
            }
        }) {
            @Override
            public String getBodyContentType() {
                return "application/json; charset=utf-8";
            }

            @Override
            public byte[] getBody() throws AuthFailureError {
                try {
                    return mRequestBody == null ? null : mRequestBody.getBytes("utf-8");
                } catch (UnsupportedEncodingException uee) {
                    VolleyLog.wtf("Unsupported Encoding while trying to get the bytes of %s using %s", mRequestBody, "utf-8");
                    return null;
                }
            }

            @Override
            protected Response<String> parseNetworkResponse(NetworkResponse response) {
                String responseString = "";
                if (response != null) {
                    responseString = String.valueOf(response.statusCode);
                }
                return Response.success(responseString, HttpHeaderParser.parseCacheHeaders(response));
            }
        };

        mQueue.add(stringRequest);

        //Mostramos lo que obtenemos
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setTitle("Recuperacion de Contraseña");
        builder.setMessage("Se ha enviado correo de recuperacion a "+emailEdit.getText().toString());
        builder.setPositiveButton("Aceptar", null);

        AlertDialog dialog = builder.create();
        dialog.show();

        //Limpiar
        emailEdit.setText("");
    }

    private void MT_IniciarSesion() {
        final EditText emailEdit = findViewById(R.id.CampoCorreo);
        final EditText Pass=findViewById(R.id.CampoPass);

        mQueue= Volley.newRequestQueue(this);
        JSONArray jsonArray;
        //Obtener Usuarios
        String url="http://192.168.0.9:3000/getUsers";
        JsonArrayRequest getrequest=new JsonArrayRequest(Request.Method.GET, url, null, new Response.Listener<JSONArray>() {
            @Override
            public void onResponse(JSONArray response) {
                for(int i=0;i<response.length();i++){
                    try {
                        JSONObject student = response.getJSONObject(i);
                        String firstName = student.getString("Nombre");
                        if(student.getString("Correo").equals(emailEdit.getText().toString())){
                            if(student.getString("Clave_Acceso").equals(Pass.getText().toString())){
                                //Admin
                                if(student.getString("FK_Rol").equals("1")){
                                    Intent intent =  new Intent(MainActivity.this, homeadmin.class);
                                    startActivity(intent);
                                    //Limpiar
                                    emailEdit.setText("");
                                    Pass.setText("");
                                }else if(student.getString("FK_Rol").equals("3")){
                                    Intent intent =  new Intent(MainActivity.this, homecliente.class);
                                    startActivity(intent);
                                    //Limpiar
                                    emailEdit.setText("");
                                    Pass.setText("");
                                }

                            }
                            break;
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


}
