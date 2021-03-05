import { Component, OnInit } from '@angular/core';
import { Router } from "@angular/router";
import { UserService } from "../../services/user.service";
import { UsersInterface } from "../../models/Users-interface";

@Component({
  selector: 'app-configuracion-usu',
  templateUrl: './configuracion-usu.component.html',
  styleUrls: ['./configuracion-usu.component.css']
})
export class ConfiguracionUsuComponent implements OnInit {

  constructor(public router: Router,public UsuService:UserService) {
    let Datos_U:UsersInterface=this.UsuService.GetCurrentUser();
    this.Nombre=Datos_U.Nombre;
    this.Apellido=Datos_U.Apellido;
    this.Password=Datos_U.Clave_Acceso;
    this.Telefono=Datos_U.Telefono.toString();
    this.Direccion=Datos_U.Direccion;
   }

  ngOnInit(): void {
  }

    //campos de la variale
    Nombre:string="";
    Apellido:string="";
    Password:string="";
    Telefono:string="";
    Direccion:string="";
  Regresar(){
    this.router.navigate(['/home_user']);
  }

  Modificar_Usu(){
    let Datos_U:UsersInterface=this.UsuService.GetCurrentUser();
    this.UsuService.UpdateUser(Datos_U.Correo,this.Nombre,this.Apellido,this.Password,this.Telefono,this.Direccion)
    .subscribe((res: UsersInterface[])=>{
      alert("Se ha Modificado Correctamente");
    })

    //Agregar a Bitacora
    var f = new Date();
    let Fecha=f.getDate() + "/" + (f.getMonth() +1) + "/" + f.getFullYear();
    this.UsuService.AddBitacora(Datos_U.Nombre,Fecha,"Se a Modificado su Cuenta")
    .subscribe((res: UsersInterface[])=>{})
    
  }

  Eliminar_Usu(){
    let Datos_U:UsersInterface=this.UsuService.GetCurrentUser();
    this.UsuService.DeleteUser(Datos_U.Correo,"Eliminado",Datos_U.Clave_Acceso)
    .subscribe((res: UsersInterface[])=>{})
    this.UsuService.Logout();
    this.router.navigate(['']);
    alert("Se ha Eliminado Correctamente");

    //Agregar a Bitacora
    var f = new Date();
    let Fecha=f.getDate() + "/" + (f.getMonth() +1) + "/" + f.getFullYear();
    this.UsuService.AddBitacora(Datos_U.Nombre,Fecha,"Se a Eliminado su Cuenta")
    .subscribe((res: UsersInterface[])=>{})
  }

}
