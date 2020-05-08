const { Router } = require('express');
const router = Router();
const BD = require('../config/configbd');

router.get('/getreporte1', async (req, res) => {
    sql = "SELECT usuario.nombre,AVG(calificacion.calificacion) FROM calificacion,usuario  WHERE usuario.no_identificacion=calificacion.id_usuario GROUP BY usuario.nombre";
    let result = await BD.Open(sql, [], false);
    BitContenido = [];

    result.rows.map(user => {
        let BitacoraOBT = {
            "Nombre":user[0],
            "Promedio":user[1]
        }

        BitContenido.push(BitacoraOBT);
    })

    res.status(200).json(BitContenido);
})
router.get('/getreporte2', async (req, res) => {
    sql = "SELECT usuario.nombre,COUNT(producto.id_categoria) FROM producto,usuario WHERE usuario.no_identificacion=producto.id_usuario GROUP BY usuario.nombre ORDER BY COUNT(producto.id_categoria) DESC FETCH FIRST 3 ROWS ONLY";
    let result = await BD.Open(sql, [], false);
    BitContenido = [];

    result.rows.map(user => {
        let BitacoraOBT = {
            "Nombre":user[0],
            "Count":user[1]
        }

        BitContenido.push(BitacoraOBT);
    })

    res.status(200).json(BitContenido);
})
router.get('/getreporte3', async (req, res) => {
    sql = "SELECT producto.descripcion, categoria.nombre FROM categoria, producto WHERE producto.id_categoria=categoria.id_categoria";
    let result = await BD.Open(sql, [], false);
    BitContenido = [];

    result.rows.map(user => {
        let BitacoraOBT = {
            "Descripcion":user[0],
            "Nombre":user[1]
        }

        BitContenido.push(BitacoraOBT);
    })

    res.status(200).json(BitContenido);
})
router.get('/getreporte4', async (req, res) => {
    sql = "SELECT producto.descripcion,COUNT(comentario),producto.fecha FROM COMENTARIO,PRODUCTO  WHERE producto.id_producto=comentario.id_producto GROUP BY producto.descripcion, producto.fecha";
    let result = await BD.Open(sql, [], false);
    BitContenido = [];

    result.rows.map(user => {
        let BitacoraOBT = {
            "Descripcion":user[0],
            "Count":user[1],
            "Fecha":user[2]

        }

        BitContenido.push(BitacoraOBT);
    })

    res.status(200).json(BitContenido);
})
router.get('/getreporte5', async (req, res) => {
    sql = "SELECT producto.descripcion,AVG(comentario.calificacion) FROM producto,comentario WHERE producto.id_producto=comentario.id_producto  GROUP BY producto.descripcion ORDER BY AVG(comentario.calificacion) ASC FETCH FIRST 3 ROWS ONLY";
    let result = await BD.Open(sql, [], false);
    BitContenido = [];

    result.rows.map(user => {
        let BitacoraOBT = {
            "Descripcion":user[0],
            "Promedio":user[1]
        }

        BitContenido.push(BitacoraOBT);
    })

    res.status(200).json(BitContenido);
})
router.get('/getreporte6', async (req, res) => {
    sql = "SELECT producto.descripcion,AVG(comentario.calificacion) FROM producto,comentario WHERE producto.id_producto=comentario.id_producto  GROUP BY producto.descripcion";
    let result = await BD.Open(sql, [], false);
    BitContenido = [];

    result.rows.map(user => {
        let BitacoraOBT = {
            "Descripcion":user[0],
            "Promedio":user[1]
        }

        BitContenido.push(BitacoraOBT);
    })

    res.status(200).json(BitContenido);
})
module.exports = router;