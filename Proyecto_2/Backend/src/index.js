const express = require('express');
const morgan = require('morgan');
const cors = require('cors');
const app = express();
const SocketIO =require('socket.io');
//Imagenes
const bodyParser = require('body-parser');  
//imports
const personRoutes = require('./routes/Users-rotes');
const mail=require("./routes/mail");
const bitacora=require("./routes/bitacora");
const calificacion=require("./routes/calificacion");
const producto=require("./routes/producto");
const reportes=require("./routes/reportes");

//settings
app.set('port', 3000);

//middlewares
app.use(morgan('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cors());
app.use(bodyParser.json());  
app.use(bodyParser.urlencoded({  
    extended: true
}));


//routes
app.use(personRoutes);
app.use(mail);
app.use(bitacora);
app.use(calificacion);
app.use(producto);
app.use(reportes);

//run
const server=app.listen(app.get('port'), () => {
    console.log('Server on Port 3000, Conectado')
});

//sockets
const io=SocketIO(server);
io.on('connection',(socket)=>{
    //console.log('user connected',socket.id);
    socket.on('new-message', (message) => {
        io.emit('new-message',message);
        //console.log(message);
    });
});
//Herramientas para Imagenes
app.use(bodyParser.json());  
app.use(bodyParser.urlencoded({  
    extended: true
}));


