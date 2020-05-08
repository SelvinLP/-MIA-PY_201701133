const { Router } = require('express');
const router = Router();
const BD = require('../config/configbd');

//Insertar Producto
router.post('/addProducto', async (req, res) => {
    const { imagen,descripcion,id_categoria,precio,fecha,cantidad,cantidaddisponible,color ,id_usuario} = req.body;

    sql = "INSERT INTO PRODUCTO ( IMAGEN,DESCRIPCION,ID_CATEGORIA,PRECIO,FECHA,CANTIDAD,CANTIDADDISPONIBLE,COLOR,ID_USUARIO ) VALUES (:imagen,:descripcion,:id_categoria,:precio,:fecha,:cantidad,:cantidaddisponible,:color,:id_usuario)";

    await BD.Open(sql, [imagen,descripcion,id_categoria,precio,fecha,cantidad,cantidaddisponible,color,id_usuario], true);

    res.status(200).json({
        "IMAGEN": imagen,
        "DESCRIPCION": descripcion,
        "ID_CATEGORIA": id_categoria,
        "PRECIO":precio,
        "FECHA":fecha,
        "CANTIDAD":cantidad,
        "CANTIDAD_DISPONIBLE":cantidaddisponible,
        "COLOR":color,
        "ID_USUARIO":id_usuario
    })
})
//Obtener Producto
router.get('/getProducto', async (req, res) => {
    sql = "SELECT * FROM PRODUCTO";
    let result = await BD.Open(sql, [], false);
    BitContenido = [];

    result.rows.map(user => {
        let BitacoraOBT = {
            "Id_Producto":user[0],
            "Imagen": user[1],
            "Descripcion": user[2],
            "Id_Categoria": user[3],
            "Precio":user[4],
            "Fecha":user[5],
            "Cantidad":user[6],
            "Cantidad_Disponible":user[7],
            "Color":user[8]
        }

        BitContenido.push(BitacoraOBT);
    })

    res.status(200).json(BitContenido);
})

//Modificar Producto
router.put("/updateProducto", async (req, res) => {
    const { descripcion,id_categoria,precio,fecha,cantidad,cantidaddisponible,color,id_producto } = req.body;
    sql = "UPDATE PRODUCTO SET DESCRIPCION=:descripcion ,ID_CATEGORIA=:id_categoria ,PRECIO=:precio ,FECHA=:fecha ,CANTIDAD=:cantidad,CANTIDADDISPONIBLE=:cantidaddisponible,COLOR=:color WHERE ID_PRODUCTO =:id_producto ";
    await BD.Open(sql, [descripcion,id_categoria,precio,fecha,cantidad,cantidaddisponible,color,id_producto ], true);
  
    res.status(200).json({})
  
})

//CATEGORIA
//Agregar Categoria
router.post('/addCategoria', async (req, res) => {
    const { nombre,descripcion,estado,fk_categoria } = req.body;

    sql = "INSERT INTO CATEGORIA ( NOMBRE,DESCRIPCION,ESTADO,FK_CATEGORIA) VALUES (:nombre ,:descripcion,:estado,:fk_categoria)";

    await BD.Open(sql, [nombre,descripcion,estado,fk_categoria], true);

    res.status(200).json({
        "NOMBRE":nombre,
        "DESCRIPCION": descripcion,
        "ESTADO": estado,
        "FK_CATEGORIA": fk_categoria
    })
})
//Obtener Categoria
router.get('/getCategoria', async (req, res) => {
    sql = "SELECT * FROM CATEGORIA ORDER BY FK_CATEGORIA ASC";
    let result = await BD.Open(sql, [], false);
    BitContenido = [];

    result.rows.map(user => {
        let BitacoraOBT = {
            "Id_Categoria":user[0],
            "Nombre":user[1],
            "Descripcion": user[2],
            "Estado": user[3],
            "Fk_Categoria": user[4]
        }

        BitContenido.push(BitacoraOBT);
    })

    res.status(200).json(BitContenido);
})
//Modificar Categoria
router.put("/updateCategoria", async (req, res) => {
    const { id_categoria,nombre,descripcion,estado,fk_categoria } = req.body;
    sql = "UPDATE CATEGORIA SET NOMBRE=:nombre,DESCRIPCION=:descripcion ,ESTADO=:estado ,FK_CATEGORIA=:fk_categoria WHERE ID_CATEGORIA =:id_categoria ";
    await BD.Open(sql, [nombre,descripcion,estado,fk_categoria,id_categoria], true);
  
    res.status(200).json({})
  
})

//Comentario
router.post('/addComentario', async (req, res) => {
    const { id_producto,calificacion,comentario } = req.body;

    sql = "INSERT INTO COMENTARIO ( ID_PRODUCTO,CALIFICACION,COMENTARIO) VALUES (:id_producto,:calificacion,:comentario)";

    await BD.Open(sql, [id_producto,calificacion,comentario], true);

    res.status(200).json({
        "ID_PRODUCTO":id_producto,
        "CALIFICACION": calificacion,
        "COMENTARIO": comentario
    })
})
router.get('/getComentario', async (req, res) => {
    sql = "SELECT * FROM COMENTARIO";
    let result = await BD.Open(sql, [], false);
    BitContenido = [];

    result.rows.map(user => {
        let BitacoraOBT = {
            "Id_Comentario":user[0],
            "Id_Producto":user[1],
            "Calificacion": user[2],
            "Comentario": user[3]
        }

        BitContenido.push(BitacoraOBT);
    })

    res.status(200).json(BitContenido);
})

module.exports = router;