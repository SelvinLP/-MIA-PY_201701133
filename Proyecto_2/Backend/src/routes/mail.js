const { Router } = require('express');
const router = Router();
const BD = require('../config/configbd');
const nodemailer=require("nodemailer");
let Datos_Usu;
//Envio de Correo
//CorreoConfirmacion
router.post("/Sendmail", (req, res) => {
    let user = req.body;
    Datos_Usu=user;
    sendMail(user, info => {
      console.log(`El Correo Se ha enviado Correctamente`);
      res.send(info);
    });
  });
  async function sendMail(user, callback) {
    let transporter = nodemailer.createTransport({
      host: "smtp.gmail.com",
      auth: {
        type: "login",
        user: "liseth.eve24@gmail.com",
        pass: "medicina2"
      }
    });
  
    let mailOptions = {
      from: '"Alie Sell"', 
      to: user.correo, 
      subject: "Bienvenido a Alie Sell",
      html: `
      <!DOCTYPE html>
      <html>
      <body>
          <h1 style="text-align:center">Bienvenido a Alie Sell: ${user.nombres}</h1>
          <h3 style="text-align:center">Para confirmar el registro del usuario, presione el siguiente Boton</h3>
          <p align="center">
          <style>
        .button {
      
          border: none;
          color: white;
          padding: 15px 32px;
          text-align: center;
          text-decoration: none;
          display: inline-block;
          font-size: 16px;
          box-shadow: 0 12px 16px 0 rgba(0,0,0,0.24), 0 17px 50px 0 rgba(0,0,0,0.19);
          padding: 15px 32px;
          background-color: #008CBA;
          width: 50%;
        }
      
        .button2 {background-color: #008CBA;}
        </style>
        <center><form action="http://localhost:3000/Verificado" align="center">
        <button (click)="CrearUsu()" type="submit" class="button button2">Confirmar Verificacion</button>
        </form></center>
        
          </p>
          <h3 style="text-align:center">Si considera que fue un error, favor de ignorar este correo</h3>
      </body>
      </html>
      `
  
    };
  
    let info = await transporter.sendMail(mailOptions);
    callback(info);
  }
  //verificacion de Correo
  router.get("/Verificado", async (req, res) => {
    const { nombres,apellidos,contraseña,correo,telefono,fotografia,genero,fecha_nacimiento,fecha_registro,direccion,credito_disponible,ganancia_obtenida,clase_cliente,estado,fk_rol } = Datos_Usu;
  
    sql = "INSERT INTO USUARIO (NOMBRE, APELLIDO, CLAVE_ACCESO, CORREO, TELEFONO, FOTOGRAFIA, GENERO, FECHA_NACIMIENTO, FECHA_REGISTRO, DIRECCION, CREDITO_DISPONIBLE, GANANCIA_OBTENIDA, CLASE_CLIENTE, ESTADO, FK_ROL) VALUES (:nombres,:apellidos,:contraseña,:correo,:telefono,:fotografia,:genero,:fecha_nacimiento,:fecha_registro,:direccion,:credito_disponible,:ganancia_obtenida,:clase_cliente,:estado,:fk_rol)";
  
    await BD.Open(sql, [nombres,apellidos,contraseña,correo,telefono,fotografia,genero,fecha_nacimiento,fecha_registro,direccion,credito_disponible,ganancia_obtenida,clase_cliente,estado,fk_rol], true);
  
    res.send(
      "<h1 style='text-align: center'>BIENVENIDO A ALLIE SELL <br><br>😃😃😃😃😃</h1><h3 style='text-align: center'>Puede cerrar esta pagina</h3>"
    );
    
  });
  

//Recuperacion de Contraseña
router.post("/SendmailRecuperacion", (req, res) => {
    let user = req.body;
    Datos_Usu=user;
    sendMail2(user, info => {
      console.log(`El Correo Se ha enviado Correctamente`);
      res.send(info);
    });
  });
  async function sendMail2(user, callback) {
    let transporter = nodemailer.createTransport({
      host: "smtp.gmail.com",
      auth: {
        type: "login",
        user: "liseth.eve24@gmail.com",
        pass: "medicina2"
      }
    });
  
    let mailOptions = {
      from: '"Alie Sell"', 
      to: user.correo, 
      subject: "Recuperacion de Contraseña",
      html: `
      <!DOCTYPE html>
      <html>
      <body>
          <h1 style="text-align:center">RECUPERACION DE CONTRASEÑA</h1>
          <h3 style="text-align:center">Presione en el siguiente boton para recuperar la contraseña </h3>
          <h4 style="text-align:center">Nueva Contraseña: ${user.contraseña} </h4>
          <p align="center">
          <style>
        .button {
      
          border: none;
          color: white;
          padding: 15px 32px;
          text-align: center;
          text-decoration: none;
          display: inline-block;
          font-size: 16px;
          box-shadow: 0 12px 16px 0 rgba(0,0,0,0.24), 0 17px 50px 0 rgba(0,0,0,0.19);
          padding: 15px 32px;
          background-color: #008CBA;
          width: 50%;
        }
      
        .button2 {background-color: #008CBA;}
        </style>
        <center><form action="http://localhost:3000/Recuperacion" align="center">
        <button (click)="CrearUsu()" type="submit" class="button button2">Confirmar Contraseña</button>
        </form></center>
        
          </p>
          <h3 style="text-align:center">Si considera que fue un error, favor de ignorar este correo</h3>
      </body>
      </html>
      `
  
    };
  
    let info = await transporter.sendMail(mailOptions);
    callback(info);
  }
  //verificacion de Correo
  router.get("/Recuperacion", async (req, res) => {
    const { contraseña,correo } = Datos_Usu;
    sql = "UPDATE USUARIO SET CLAVE_ACCESO =:contraseña WHERE CORREO =:correo";
    await BD.Open(sql, [contraseña,correo],true);

    res.send(
        "<h1 style='text-align: center'>SE HA RECUPERADO LA CONTRASEÑA CORRECTAMENTE <br><br>😃😃😃😃😃</h1><h3 style='text-align: center'>Puede cerrar esta pagina</h3>"
    );
    
  });

module.exports = router;