const { Router } = require('express');
const router = Router();
const BD = require('../config/configbd');

//Mostrar Usuarios
router.get('/getUsers', async (req, res) => {
    sql = "SELECT * FROM USUARIO";

    let result = await BD.Open(sql, [], false);
    Users = [];

    result.rows.map(user => {
        let userOBT = {
            "No_Identificacion": user[0],
            "Nombre": user[1],
            "Apellido": user[2],
            "Clave_Acceso": user[3],
            "Correo": user[4],
            "Telefono": user[5],
            "Fotografia": user[6],
            "Genero": user[7],
            "fecha_Nacimiento": user[8],
            "fecha_Registro": user[9],
            "Direccion": user[10],
            "Credito_Disponible": user[11],
            "Ganancia_Obtenida": user[12],
            "Clase_Cliente": user[13],
            "Estado": user[14],
            "FK_Rol": user[15]
        }

        Users.push(userOBT);
    })

    res.status(200).json(Users);
})

//Insertar Usuario
router.post('/addUsers', async (req, res) => {
    const { nombres,apellidos,contraseña,correo,telefono,fotografia,genero,fecha_nacimiento,fecha_registro,direccion,credito_disponible,ganancia_obtenida,clase_cliente,estado,fk_rol } = req.body;

    sql = "INSERT INTO USUARIO (NOMBRE, APELLIDO, CLAVE_ACCESO, CORREO, TELEFONO, FOTOGRAFIA, GENERO, FECHA_NACIMIENTO, FECHA_REGISTRO, DIRECCION, CREDITO_DISPONIBLE, GANANCIA_OBTENIDA, CLASE_CLIENTE, ESTADO, FK_ROL) VALUES (:nombres,:apellidos,:contraseña,:correo,:telefono,:fotografia,:genero,:fecha_nacimiento,:fecha_registro,:direccion,:credito_disponible,:ganancia_obtenida,:clase_cliente,:estado,:fk_rol)";

    await BD.Open(sql, [nombres,apellidos,contraseña,correo,telefono,fotografia,genero,fecha_nacimiento,fecha_registro,direccion,credito_disponible,ganancia_obtenida,clase_cliente,estado,fk_rol], true);

    res.status(200).json({
        "NOMBRE": nombres,
        "APELLIDO": apellidos,
        "CLAVE_ACCESO": contraseña,
        "CORREO": correo,
        "TELEFONO": telefono,
        "FOTOGRAFIA": fotografia,
        "GENERO": genero,
        "FECHA_NACIMIENTO": fecha_nacimiento,
        "FECHA_REGISTRO": fecha_registro,
        "DIRECCION": direccion,
        "CREDITO_DISPONIBLE": credito_disponible,
        "GANANCIA_OBTENIDA": ganancia_obtenida,
        "CLASE_CLIENTE": clase_cliente,
        "ESTADO": estado,
        "FK_ROL":fk_rol
    })
})

//Actualizar Usuario
router.put("/updateUsers", async (req, res) => {
  const { correo,nombres, apellidos, contraseña, telefono,direccion } = req.body;
  sql = "UPDATE USUARIO SET NOMBRE=:nombres, APELLIDO=:apellidos,TELEFONO=:telefono,CLAVE_ACCESO =:contraseña,DIRECCION=:direccion WHERE CORREO =:correo";
  await BD.Open(sql, [nombres, apellidos,telefono,contraseña,direccion,correo ], true);

  res.status(200).json({
    "correo":correo,
    "nombres":nombres,
    "apellidos":apellidos,
    "contraseña":contraseña,
    "telefono":telefono,
    "direccion":direccion
  })

})

//Actualizar Usuario en Administrador
router.put("/updateUsersAdmin", async (req, res) => {
  const { correo,nombres, apellidos, contraseña, telefono,direccion,genero,fecha_nacimiento,rol } = req.body;
  sql = "UPDATE USUARIO SET NOMBRE=:nombres, APELLIDO=:apellidos,TELEFONO=:telefono,CLAVE_ACCESO =:contraseña,DIRECCION=:direccion,GENERO=:genero, FECHA_NACIMIENTO=:fecha_nacimiento,FK_ROL=:rol WHERE CORREO =:correo";
  await BD.Open(sql, [nombres, apellidos,telefono,contraseña,direccion,genero,fecha_nacimiento,rol,correo ], true);

  res.status(200).json({})

})

//Eliminar Usuario
router.put("/deleteUsers", async (req, res) => {
  const { correo,estado,password } = req.body;
  sql = "UPDATE USUARIO SET ESTADO=:estado WHERE CORREO =:correo AND CLAVE_ACCESO =:password";
  await BD.Open(sql, [estado,correo,password ], true);

  res.status(200).json({
    "estado":estado
  })

})

//Subir Imagenes  
const multipart = require('connect-multiparty');  

const multipartMiddleware = multipart({  
    uploadDir: '../Frontend/src/assets'
});

router.post('/api/upload', multipartMiddleware, (req, res, next) => {  
  res.json({
      'message': req.files.image.path
  });
});
module.exports = router;