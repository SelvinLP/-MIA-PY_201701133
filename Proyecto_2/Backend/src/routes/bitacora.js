const { Router } = require('express');
const router = Router();
const BD = require('../config/configbd');
const nodemailer=require("nodemailer");
let Datos_Usu;

//Insertar Bitacora
router.post('/addBitacora', async (req, res) => {
    const { usuario,fecha,contenido } = req.body;

    sql = "INSERT INTO BITACORA ( USUARIO,FECHA,CONTENIDO ) VALUES (:usuario,:fecha,:contenido)";

    await BD.Open(sql, [usuario,fecha,contenido], true);

    res.status(200).json({
        "USUARIO": usuario,
        "FECHA": fecha,
        "CONTENIDO": contenido
    })
})
//Obtener Bitacora
router.get('/getBitacora', async (req, res) => {
    sql = "SELECT * FROM BITACORA";
    let result = await BD.Open(sql, [], false);
    BitContenido = [];

    result.rows.map(user => {
        let BitacoraOBT = {
            "Id":user[0],
            "Usuario": user[1],
            "Fecha": user[2],
            "Contenido": user[3]
        }

        BitContenido.push(BitacoraOBT);
    })

    res.status(200).json(BitContenido);
})
module.exports = router;