import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';

//Imports
import { HomeComponent } from './conponents/home/home.component';
import { CrearUsuarioComponent } from "./conponents/crear-usuario/crear-usuario.component";
import { HomeUserComponent } from "./conponents/home-user/home-user.component";

import { FormsModule } from "@angular/forms";
import { HttpClientModule } from "@angular/common/http";
import { ConfiguracionUsuComponent } from './conponents/configuracion-usu/configuracion-usu.component';
import { HomeAdminComponent } from './conponents/home-admin/home-admin.component';
import { HomeServicioAyudaComponent } from './conponents/home-servicio-ayuda/home-servicio-ayuda.component';
import { ViewBitacoraComponent } from './conponents/view-bitacora/view-bitacora.component';
import { ChatComponent } from './conponents/chat/chat.component';
import { ChatService } from "./services/chat.service";
import { ProductoyCategoriaComponent } from './conponents/productoy-categoria/productoy-categoria.component';
import { ReportesComponent } from './conponents/reportes/reportes.component';


@NgModule({
  declarations: [
    AppComponent,
    HomeComponent,
    CrearUsuarioComponent,
    HomeUserComponent,
    ConfiguracionUsuComponent,
    HomeAdminComponent,
    HomeServicioAyudaComponent,
    ViewBitacoraComponent,
    ChatComponent,
    ProductoyCategoriaComponent,
    ReportesComponent
  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    FormsModule,
    HttpClientModule
  ],
  providers: [ChatService],
  bootstrap: [AppComponent]
})
export class AppModule { }
