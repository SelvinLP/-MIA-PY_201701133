package com.example.proyecto2;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.EditText;

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

public class CrudUsuario extends AppCompatActivity {
    private RequestQueue mQueue;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_crud_usuario);

        findViewById(R.id.buttonRegistrar).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                MandarCorreo();
            }
        });
        findViewById(R.id.buttonRegistrar4).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                BuscarCorreo();
            }
        });
        findViewById(R.id.buttonRegistrar2).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                ModificarUsu();
            }
        });

        findViewById(R.id.buttonRegistrar3).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                EliminarUsu();
            }
        });
    }
    private void MandarCorreo() {
        //Datos
        final EditText Nombre = findViewById(R.id.CampoNombreC);
        final EditText Apellido = findViewById(R.id.campoApellidoC);
        final EditText Correo = findViewById(R.id.CampoCorreoC);
        final EditText Pass = findViewById(R.id.CampoPass);
        final EditText Telefono = findViewById(R.id.CampoCel);
        final EditText Genero = findViewById(R.id.CampoGenero);
        final EditText Fecha = findViewById(R.id.CampoFecha);
        final EditText Dirrecion = findViewById(R.id.CampoDireccion);

        String url = "http://192.168.0.9:3000/Sendmail";

        mQueue= Volley.newRequestQueue(this);
        JSONObject jsonBodyObj = new JSONObject();
        try{
            jsonBodyObj.put("nombres",Nombre.getText().toString());
            jsonBodyObj.put("apellidos",Apellido.getText().toString());
            jsonBodyObj.put("contraseña",Pass.getText().toString());
            jsonBodyObj.put("correo",Correo.getText().toString());
            jsonBodyObj.put("telefono",Telefono.getText().toString());
            jsonBodyObj.put("fotografia","");
            jsonBodyObj.put("genero",Genero.getText().toString());
            jsonBodyObj.put("fecha_nacimiento",Fecha.getText().toString());
            jsonBodyObj.put("fecha_registro","");
            jsonBodyObj.put("direccion", Dirrecion.getText().toString());
            jsonBodyObj.put("credito_disponible","1000");
            jsonBodyObj.put("ganancia_obtenida","");
            jsonBodyObj.put("clase_cliente","Oro");
            jsonBodyObj.put("estado","Conectado");
            jsonBodyObj.put("fk_rol","3");
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
        builder.setTitle("Registros de Usuario");
        builder.setMessage("Se ha enviado correo de veificacion a "+Correo.getText().toString());
        builder.setPositiveButton("Aceptar", null);

        AlertDialog dialog = builder.create();
        dialog.show();

        //Limpiar
        Nombre.setText("");
        Apellido.setText("");
        Correo.setText("");
        Pass.setText("");
        Telefono.setText("");
        Genero.setText("");
        Fecha.setText("");
        Dirrecion.setText("");
    }

    private void BuscarCorreo(){
        final EditText Nombre = findViewById(R.id.CampoNombreC);
        final EditText Apellido = findViewById(R.id.campoApellidoC);
        final EditText Correo = findViewById(R.id.CampoCorreoC);
        final EditText Pass = findViewById(R.id.CampoPass);
        final EditText Telefono = findViewById(R.id.CampoCel);
        final EditText Genero = findViewById(R.id.CampoGenero);
        final EditText Fecha = findViewById(R.id.CampoFecha);
        final EditText Dirrecion = findViewById(R.id.CampoDireccion);;

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
                        if(student.getString("Correo").equals(Correo.getText().toString())){
                            if(student.getString("Clave_Acceso").equals(Pass.getText().toString())){
                                Nombre.setText(student.getString("Nombre"));
                                Apellido.setText(student.getString("Apellido"));
                                Telefono.setText(student.getString("Telefono"));
                                Genero.setText(student.getString("Genero"));
                                Fecha.setText(student.getString("fecha_Nacimiento"));
                                Dirrecion.setText(student.getString("Direccion"));
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

    private  void ModificarUsu(){
        //Datos
        final EditText Nombre = findViewById(R.id.CampoNombreC);
        final EditText Apellido = findViewById(R.id.campoApellidoC);
        final EditText Correo = findViewById(R.id.CampoCorreoC);
        final EditText Pass = findViewById(R.id.CampoPass);
        final EditText Telefono = findViewById(R.id.CampoCel);
        final EditText Genero = findViewById(R.id.CampoGenero);
        final EditText Fecha = findViewById(R.id.CampoFecha);
        final EditText Dirrecion = findViewById(R.id.CampoDireccion);

        String url = "http://192.168.0.9:3000/updateUsersAdmin";

        mQueue= Volley.newRequestQueue(this);
        JSONObject jsonBodyObj = new JSONObject();
        try{
            jsonBodyObj.put("correo",Correo.getText().toString());
            jsonBodyObj.put("nombres",Nombre.getText().toString());
            jsonBodyObj.put("apellidos",Apellido.getText().toString());
            jsonBodyObj.put("contraseña",Pass.getText().toString());
            jsonBodyObj.put("telefono",Telefono.getText().toString());
            jsonBodyObj.put("direccion", Dirrecion.getText().toString());
            jsonBodyObj.put("genero",Genero.getText().toString());
            jsonBodyObj.put("fecha_nacimiento",Fecha.getText().toString());
            jsonBodyObj.put("rol","3");
        }catch (JSONException e){
            e.printStackTrace();
        }

        final String mRequestBody = jsonBodyObj.toString();

        StringRequest stringRequest = new StringRequest(Request.Method.PUT, url, new Response.Listener<String>() {
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
        builder.setTitle("Crud Usuarios");
        builder.setMessage("Se ha Modificado Correcamente el Usuario");
        builder.setPositiveButton("Aceptar", null);

        AlertDialog dialog = builder.create();
        dialog.show();

        //Limpiar
        Nombre.setText("");
        Apellido.setText("");
        Correo.setText("");
        Pass.setText("");
        Telefono.setText("");
        Genero.setText("");
        Fecha.setText("");
        Dirrecion.setText("");
    }

    private  void EliminarUsu(){
        //Datos
        final EditText Nombre = findViewById(R.id.CampoNombreC);
        final EditText Apellido = findViewById(R.id.campoApellidoC);
        final EditText Correo = findViewById(R.id.CampoCorreoC);
        final EditText Pass = findViewById(R.id.CampoPass);
        final EditText Telefono = findViewById(R.id.CampoCel);
        final EditText Genero = findViewById(R.id.CampoGenero);
        final EditText Fecha = findViewById(R.id.CampoFecha);
        final EditText Dirrecion = findViewById(R.id.CampoDireccion);

        String url = "http://192.168.0.9:3000/deleteUsers";

        mQueue= Volley.newRequestQueue(this);
        JSONObject jsonBodyObj = new JSONObject();
        try{
            jsonBodyObj.put("correo",Correo.getText().toString());
            jsonBodyObj.put("estado","Eliminado");
            jsonBodyObj.put("password",Pass.getText().toString());
        }catch (JSONException e){
            e.printStackTrace();
        }

        final String mRequestBody = jsonBodyObj.toString();

        StringRequest stringRequest = new StringRequest(Request.Method.PUT, url, new Response.Listener<String>() {
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
        builder.setTitle("Crud Usuarios");
        builder.setMessage("Se ha Eliminado Correcamente el Usuario");
        builder.setPositiveButton("Aceptar", null);

        AlertDialog dialog = builder.create();
        dialog.show();

        //Limpiar
        Nombre.setText("");
        Apellido.setText("");
        Correo.setText("");
        Pass.setText("");
        Telefono.setText("");
        Genero.setText("");
        Fecha.setText("");
        Dirrecion.setText("");

    }
}
