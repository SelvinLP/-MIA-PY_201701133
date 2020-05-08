const { Router } = require('express');
const router = Router();
const BD = require('../config/configbd');

//Insertar Calificacion
router.post('/addCalificacionServicio', async (req, res) => {
    const { Id_Usuario,Calificacion,Descripcion} = req.body;

    sql = "INSERT INTO CALIFICACION  ( ID_USUARIO,CALIFICACION,DESCRIPCION ) VALUES (:Id_Usuario,:Calificacion,:Descripcion)";

    await BD.Open(sql, [Id_Usuario,Calificacion,Descripcion], true);

    res.status(200).json({
        "ID_USUARIO": Id_Usuario,
        "CALIFICACION": Calificacion,
        "DESCRIPCION": Descripcion
    })
})
//Obtener Calificacion
router.get('/getCalificacionServicio', async (req, res) => {
    sql = "SELECT * FROM CALIFICACION";
    let result = await BD.Open(sql, [], false);
    BitContenido = [];

    result.rows.map(user => {
        let BitacoraOBT = {
            "Id_Calificacion":user[0],
            "Id_Usuario":user[1],
            "Calificacion": user[2],
            "Descripcion": user[3]
        }

        BitContenido.push(BitacoraOBT);
    })

    res.status(200).json(BitContenido);
})
module.exports = router;