#Contenido de calificacion.sh
#Crea 5 discos de 50 Mb
#exec -path=/home/andhy/Escritorio/Entrada.sh
#CREANDO DISCOS ----------------------------------------------------------------------------------------
mkdisk -fit=BF -unit=M -size=50 -path="/home/archivos/fase1/Disco1.disk" 
mkdisk -unit=K -size=51200 -path="/home/archivos/fase1/Disco2.disk" -fit=BF
#mkDisk -size=10 -path="/home/archivos/fase1/Disco4.disk" -unit=k -fit=BF
#mkdisk -size=51200 -unit=k -path="/home/archivos/fase1/mis archivos/Disco3.disk" -fit=BF
#mkdisk -size=51200 -unit=k -path="/home/archivos/fase1/mis archivos/archivos/Disco5.disk" -fit=BF

#Debería dar error
#mkDisk  -size=30 -path=/home/archivos/fase1/Disco4.disk

#ELIMINANDO DISCOS ------------------------------------------------------------------------------------
#Elimina un D, el primero debería dar error
#rmDisk -path=/home/Disco4.disk
#rmDisk -path=/home/archivos/fase1/Disco2.disk
#rmDisk -path="/home/archivos/fase1/mis archivos/Disco3.disk"

#CREANDO PARTICIONES ----------------------------------------------------------------------------------
#Crear particiones Disco1.disk
fdisk -type=P -unit=K -name=Part1 -size=7680 -path=/home/archivos/fase1/Disco1.disk -fit=BF
fdisk -type=E -unit=K -name=Part2 -size=7680 -path=/home/archivos/fase1/Disco1.disk -fit=FF
fdisk -type=E -unit=K -name=Part3 -size=7680 -path=/home/archivos/fase1/Disco1.disk -fit=WF #Debe dar error por que ya existe una extendida
fdisk -type=P -unit=K -name=Part3 -size=7680 -path=/home/archivos/fase1/Disco1.disk -fit=WF
fdisk -type=P -unit=K -name=Part4 -size=7680 -path=/home/archivos/fase1/Disco1.disk -fit=BF
fdisk -type=L -unit=K -name=Part5 -size=1270 -path=/home/archivos/fase1/Disco1.disk -fit=BF
fdisk -type=L -unit=K -name=Part6 -size=1270 -path=/home/archivos/fase1/Disco1.disk -fit=BF
fdisk -type=L -unit=K -name=Part7 -size=1270 -path=/home/archivos/fase1/Disco1.disk -fit=WF
fdisk -type=L -unit=K -name=Part8 -size=1270 -path=/home/archivos/fase1/Disco1.disk -fit=WF
fdisk -type=L -unit=K -name=Part9 -size=1270 -path=/home/archivos/fase1/Disco1.disk -fit=BF
fdisk -type=L -unit=K -name=Part10 -size=1270 -path=/home/archivos/fase1/Disco1.disk -fit=BF
fdisk -type=L -unit=K -name=Part10 -size=1270 -path=/home/archivos/fase1/Disco1.disk -fit=BF #debe dar error ya existe part10;

#Crear particiones Disco2.disk
fdisk -type=L -unit=K -name=Part28 -size=7680 -path=/home/archivos/fase1/Disco2.disk -fit=WF #Debe dar error porque no existe una extendida
fdisk -type=L -unit=K -name=Part27 -size=7680 -path=/home/archivos/fase1/Disco2.disk -fit=WF #Debe dar error porque no existe una extendida
fdisk -type=P -unit=K -name=Part12 -size=4680 -path=/home/archivos/fase1/Disco2.disk -fit=BF
fdisk -type=P -unit=K -name=Part13 -size=4680 -path=/home/archivos/fase1/Disco2.disk -fit=WF
fdisk -type=P -unit=K -name=Part14 -size=4680 -path=/home/archivos/fase1/Disco2.disk -fit=BF
fdisk -type=E -unit=K -name=Part15 -size=17360 -path=/home/archivos/fase1/Disco2.disk -fit=WF
fdisk -type=L -unit=K -name=Part16 -size=1200 -path=/home/archivos/fase1/Disco2.disk -fit=BF
fdisk -type=L -unit=K -name=Part17 -size=1200 -path=/home/archivos/fase1/Disco2.disk -fit=BF
fdisk -type=L -unit=K -name=Part18 -size=1200 -path=/home/archivos/fase1/Disco2.disk -fit=WF
fdisk -type=L -unit=K -name=Part19 -size=1200 -path=/home/archivos/fase1/Disco2.disk -fit=WF
fdisk -type=L -unit=K -name=Part20 -size=1200 -path=/home/archivos/fase1/Disco2.disk -fit=BF
fdisk -type=L -unit=K -name=Part21 -size=1200 -path=/home/archivos/fase1/Disco2.disk -fit=BF
fdisk -type=L -unit=K -name=Part22 -size=1200 -path=/home/archivos/fase1/Disco2.disk -fit=BF
fdisk -type=L -unit=K -name=Part23 -size=1200 -path=/home/archivos/fase1/Disco2.disk -fit=BF
fdisk -type=L -unit=K -name=Part24 -size=1200 -path=/home/archivos/fase1/Disco2.disk -fit=BF
fdisk -type=L -unit=K -name=Part25 -size=1200 -path=/home/archivos/fase1/Disco2.disk -fit=BF

#Monta las particiones Disco1.disk
mount -path=/home/archivos/fase1/Disco1.disk -name=Part1 #vda1
mount -path=/home/archivos/fase1/Disco2.disk -name=Part9 #Debe dar error por que no existe
mount -path=/home/archivos/fase1/Disco1.disk -name=Part8 #vda2
mount -path=/home/archivos/fase1/Disco1.disk -name=Part7 #vda3
mount -path=/home/archivos/fase1/Disco1.disk -name=Part6 #vda4
mount -path=/home/archivos/fase1/Disco1.disk -name=Part2 #vda5
mount -path=/home/archivos/fase1/Disco1.disk -name=Part3 #vda6
mount -path=/home/archivos/fase1/Disco2.disk -name=Part12 #vdb1
mount -path=/home/archivos/fase1/Disco2.disk -name=Part13 #vdb2
mount -path=/home/archivos/fase1/Disco2.disk -name=Part14 #vdb3
mount -path=/home/archivos/fase1/Disco2.disk -name=Part15 #vdb4
mount -path=/home/archivos/fase1/Disco2.disk -name=Part16 #vdb5
mount -path=/home/archivos/fase1/Disco2.disk -name=Part17 #vdb6
mount -path=/home/archivos/fase1/Disco2.disk -name=Part18 #vdb7
mount -path=/home/archivos/fase1/Disco2.disk -name=Part19 #vdb8
mount -path=/home/archivos/fase1/Disco2.disk -name=Part20 #vdb9
mount -path=/home/archivos/fase1/Disco2.disk -name=Part21 #vdb10
mount -path=/home/archivos/fase1/Disco2.disk -name=Part22 #vdb11
mount -path=/home/archivos/fase1/Disco2.disk -name=Part23 #vdb12
mount -path=/home/archivos/fase1/Disco2.disk -name=Part24 #vdb13
mount -path=/home/archivos/fase1/Disco2.disk -name=Part25 #vdb14 Debe dar error por qu no existe

#Desmontar las particiones
#unmount -id=vda4
#Desmontar Error
#unmount -id=vdx1
#Creando reportes
rep -id=vda1 -Path=/home/mia/mbr1.png -name=mbr 
rep -id=vda1 -Path=/home/mia/disk1.png -name=disk
#rep -id=vdb1 -Path=/home/mia/mbr4.png -name=mbr 
#rep -id=vdb1 -Path=/home/mia/disk4.png -name=disk

#Eliminando particiones
fdisk -delete=fast -name=Part1 -path=/home/archivos/fase1/Disco1.disk
fdisk -delete=fast -name=Part6 -path=/home/archivos/fase1/Disco1.disk
fdisk -delete=fast -name=Part10 -path=/home/archivos/fase1/Disco1.disk
fdisk -delete=fast -name=Part9 -path=/home/archivos/fase1/Disco1.disk #PART 9 NO EXISTE XQ DIO ERROR

#Eliminando y agregando espacio tamaño de particiones
fdisk -delete=full -unit=K -path=/home/archivos/fase1/Disco2.disk -name=Part14 
fdisk -add=1 -unit=K -path=/home/archivos/fase1/Disco2.disk -name=Part13
#ERROR
#Creando reportes
rep -id=vda1 -Path=/home/mia/mbr2.png -name=mbr 
rep -id=vda1 -Path=/home/mia/disk2.png -name=disk
#rep -id=vdb1 -Path=/home/mia/mbr5.png -name=mbr 
#rep -id=vdb1 -Path=/home/mia/disk5.png -name=disk

#Eliminando tamaño de particiones
fdisk -add=-700 -unit=K -path=/home/archivos/fase1/Disco1.disk -name=Part3 
fdisk -add=-800 -unit=K -path=/home/archivos/fase1/Disco1.disk -name=Part4
fdisk -add=-200 -unit=K -path=/home/archivos/fase1/Disco1.disk -name=Part11
fdisk -add=-400 -unit=K -path=/home/archivos/fase1/Disco1.disk -name=Part8
fdisk -add=-1000 -unit=K -path=/home/archivos/fase1/Disco1.disk -name=Part13

fdisk -add=-1000 -unit=K -path=/home/archivos/fase1/Disco1.disk -name=Part13


#Creando reportes
#rep -id=vda1 -Path=/home/mia/mbr3.png -name=mbr 
#rep -id=vda1 -Path=/home/mia/disk3.png -name=disk
#rep -id=vdb1 -Path=/home/mia/mbr6.png -name=mbr 
#rep -id=vdb1 -Path=/home/mia/disk6.png -name=disk

#Formateo de Particiones
mkfs -type=fast -id=vda1 -fs=3fs
#mkfs -type=full -id=vdb1

#login 
login -id=vda1 -usr=root -pwd=123
logout
logout
login -id=vda1 -usr=root -pwd=123

#Creacion de grupo
mkgrp -name="hola adios"
mkgrp -name=si2
mkgrp -name="hola adios" #ya existe
mkgrp -name=si3
#Crear Usuario
mkusr -grp="hola adios" -usr=root -pwd=123 #usuario ya existe
mkusr -grp=si2 -usr=Nuevo -pwd=234
mkusr -grp=si2 -usr=Nuevo2 -pwd=234
mkusr -grp="hola adios" -usr=hola1 -pwd=234
mkusr -grp="hola adios" -usr=hola2 -pwd=234

#Eliminar grupo
rmgrp -name="hola adios"
mkgrp -name="R hola" 
mkusr -grp="hola adios" -usr=Intento -pwd=593 #no se puede crear grupo no existe
mkusr -grp=si2 -usr=Nuevo3 -pwd=0923
mkusr -grp="R hola" -usr=YES -pwd=si
#Eliminar Usuario
rmusr -usr=Nuevo2
rmusr -usr=Nuevo2
mkusr -grp=si2 -usr=POSICION2 -pwd=234
rmusr -usr=POSICION2
#Reporte Super Bloque
unmount -id=vda1
pause
mount -path=/home/archivos/fase1/Disco1.disk -name=Part1 #vda1

#MKDIR
mkdir -Path=/Intento1
mkdir -path="/home/archivos/mia/fase2" -p
#Cambio de Permisos
chmod -path="/home/archivos/mia" -ugo=555 -R
pause
#MKFILE
mkfile -p -path="/home/archivos/mia/fase2/b64/hola.txt" -size=70
cat -file="/home/archivos/mia/fase2/b64/hola.txt"
edit -path="/home/archivos/mia/fase2/b64/hola.txt" -cont="Editado"
ren -path="/home/archivos/mia/fase2/b64" -name="Editado2"
#cat -file="/Users.txt"
#copiar
#cp path="/home/archivos/mia/fase2" -dest=/Intento1
#busqueda con find
find -path="/archivos" -name=hola.txt
pause

#Cambio de Propetario
chown -path="/home/archivos/mia" -usr=Nuevo3 -r
#Cambio de Grupo
chgrp -usr=YES -grp=si2
pause
#Reporte TREE
rep -id=vda1 -name=bm_inode -Path=/home/mia/bm1_inode.png
rep -id=vda1 -name=bm_block -Path=/home/mia/bm1_block.png
rep -id=vda1 -name=file -path=/home/mia/filerep.png -ruta="/home/archivos/mia/fase2/Editado2/hola.txt"
rep -id=vda1 -name=inode -Path=/home/mia/Linode.png
rep -id=vda1 -name=block -Path=/home/mia/Lblock.png
rep -id=vda1 -name=sb -Path=/home/mia/SuperBloque1.png
rep -id=vda1 -name=tree -Path=/home/mia/TREE.png
rep -id=vda1 -name=journaling -Path=/home/mia/repor.png

#perdida
#loss -id=vda1

#reportes de perdidas
#rep -id=vda1 -name=bm_inode -Path=/home/mia/bm1_inode_perdida.png
#rep -id=vda1 -name=bm_block -Path=/home/mia/bm1_block_perdida.png
#rep -id=vda1 -name=inode -Path=/home/mia/Linode_perdida.png
#rep -id=vda1 -name=block -Path=/home/mia/Lblock_perdida.png
#rep -id=vda1 -name=sb -Path=/home/mia/SuperBloque1_perdida.png
#rep -id=vda1 -name=tree -Path=/home/mia/TREE_perdida.png
#rep -id=vda1 -name=journaling -Path=/home/mia/repor_perdida.png

#recovery -id=vda1
#recuperacion
#rep -id=vda1 -name=bm_inode -Path=/home/mia/bm1_inode_recuperacion.png
#rep -id=vda1 -name=bm_block -Path=/home/mia/bm1_block_recuperacion.png
#rep -id=vda1 -name=inode -Path=/home/mia/Linode_recuperacion.png
#rep -id=vda1 -name=block -Path=/home/mia/Lblock_recuperacion.png
#rep -id=vda1 -name=sb -Path=/home/mia/SuperBloque1_recuperacion.png
#rep -id=vda1 -name=tree -Path=/home/mia/TREE_recuperacion.png
rep -id=vda1 -name=ls -ruta="/home/archivos/mia/fase2/Editado2/hola.txt" -Path=/home/mia/reportels.png
pause

