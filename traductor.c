# incluir  " ansintac.c "

ARCHIVO *salida;	  // archivo de salida
int espacios = 0 ; // espacios para lograr el formato de salida deseado

vacío  elemento_trad ();
vacío  array_trad ();
void  arrayA_trad ();
vacío  element_list_trad ();
vacío  element_listA_trad ();
vacío  objeto_trad ();
void  objetoA_trad ();
void  atributo_trad ();
vacío  atributos_lista_trad ();
void  atributos_listaA_trad ();
void  nombre_atributo_trad ();
vacío  atributo_valor_trad ();


void  imprimir_esp (){
    int i= 0 ;
    for (i= 1 ;i<=espacios;i++){
        fprintf (salida, "  " );
    }
}


// cadena sin comillas
void  string_trad ( char * cadena){
    cadena de caracteres [ TAMLEX ];
    strcpy (cadena,cadena);
    int i= 1 ;
    while (cadena[i] != ' " ' ){
        fprintf (salida, " %c " ,cadena[i]);
        yo++;
    }
}


// json_trad -> elemento_trad EOF
vacío  json_trad (){
    elemento_trad ();
}


// elemento_trad -> objeto_trad | array_trad
vacío  elemento_trad (){
    si (t. compLex == ' { ' ){
        objeto_trad ();
    } más  si (t. compLex == ' [ ' ){
        matriz_trad ();
    }  
}


// array_trad -> [ arrayA_trad
vacío  array_trad (){  
    si (t. compLex == ' [ ' ){
        coincidencia ( ' [ ' );
        matrizA_trad ();
    }
}


// arrayA_trad -> lista-de-elementos ] | ]
 matriz vacíaA_trad ( ){
    if (t. compLex == ' { ' || t. compLex == ' [ ' ){
        fprintf (salida, " \n " );
        imprimir_esp ();
        fprintf (salida, " <elemento> \n " );
        espacios+= 4 ;
        lista_elementos_trad ();
        coincidencia ( ' ] ' );
        imprimir_esp ();
        fprintf (salida, " </elemento> \n " );
        espacios-= 4 ;
        imprimir_esp ();
    } más  si (t. compLex == ' ] ' ){
        espacios-= 4 ;
        coincidencia ( ' ] ' );
    }
}


// lista-de-elementos_trad -> elemento_trad lista-de-elementos_trad
vacío  element_list_trad (){
    if (t. compLex == ' { ' || t. compLex == ' [ ' ){
        elemento_trad ();
        lista_elementosA_trad ();    
    }
}


// elemento-listaA_trad -> ,elemento_trad elemento-listaA_trad | ε
vacío  element_listA_trad (){
    si (t. compLex == ' ] ' ){
        volver ;
    }

    si (t. compLex == ' , ' ){  
        coincidencia ( ' , ' );
        imprimir_esp ();
        fprintf (salida, " </elemento> \n " );
        imprimir_esp ();
        fprintf (salida, " <elemento> \n " );
        espacios+= 4 ;
        elemento_trad ();
        lista_elementosA_trad ();   
    }
}


// objeto_trad -> { objetoA_trad
 objeto vacío_trad ( ){
    si (t. compLex == ' { ' ){
        coincidencia ( ' { ' );
        objetoA_trad ();
    }

}


// objetoA_trad -> lista-atributos_trad } | }
void  objetoA_trad (){
    if (t. compLex == CADENA){
        lista_atributos_trad ();
        coincidencia ( ' } ' );

    } más  si (t. compLex == ' } ' ){
        coincidencia ( ' } ' );
    }
}


// lista-atributos_trad -> atributo_trad lista-atributosA_trad
vacío  atributos_lista_trad (){
    if (t. compLex == CADENA){
        atributo_trad ();
        atributos_listaA_trad ();
    }
}


// atributos-listaA_trad -> ,atributos_trad atributos-listaA_trad | ε
void  atributos_listaA_trad (){
    si (t. compLex == ' } ' ){
        espacios-= 4 ;
        volver ;
    }

    si (t. compLex == ' , ' ){
        coincidencia ( ' , ' );
        atributo_trad ();
        atributos_listaA_trad ();
    }
}


// atributo_trad -> atributo-nombre_trad : atributo-valor_trad
vacío  atributo_trad (){
    if (t. compLex == CADENA){
        imprimir_esp ();
        char lexema[TAMLEX];
        strcpy (lexema,t. pe -> lexema );
        fprintf (salida, " < " );
        atributo_nombre_trad ();
        fprintf (salida, " > " );
        coincidencia ( ' : ' );
        atributo_valor_trad ();
        fprintf (salida, " </ " );
        string_trad (lexema);
        fprintf (salida, " > \n " );    
    }
}


// atributo-nombre_trad -> string_trad
void  nombre_atributo_trad (){
    if (t. compLex == CADENA){    
        string_trad (t. pe -> lexema );
        partido (CADENA);
    }
}


// atributo-valor_trad -> elemento_trad | CADENA | NÚMERO | VERDADERO | FALSO | NULO
vacío  atributo_valor_trad (){
    if (t. compLex == ' { ' || t. compLex == ' [ ' ){
        espacios += 4 ;
        elemento_trad ();
    } más  si (t. compLex == CADENA){
        fprintf (salida, " %s " ,t. pe -> lexema );
        partido (CADENA);
    } más  si (t. compLex == NUM){
        fprintf (salida, " %s " ,t. pe -> lexema );
        coincidencia (NÚM);
    } más  si (t. compLex == VERDADERO ){
        fprintf (salida, " %s " ,t. pe -> lexema );
        coincidencia ( VERDADERO );
    } más  si (t. compLex == FALSO ){
        fprintf (salida, " %s " ,t. pe -> lexema );
        coincidencia ( FALSO );
    } más  si (t. compLex == A_NULL){
        fprintf (salida, " %s " ,t. pe -> lexema );
        coincidencia (A_NULL);
    }
}


int  main ( int argc, char * args[]){
    initTabla ();
	initTablaSimbolos ();
    si (argc > 1 ){
        if (!(archivo= fopen (args[ 1 ], " rt " ))){
            printf ( " Archivo no encontrado. \n " );
            salida ( 1 );
        }
        obtenerToken ();
        json ();
        si (correcto){
            salida = fopen ( " salida.xml " , " w " );
            fclose (archivo);
            archivo= fopen (args[ 1 ], " rt " );
            obtenerToken ();
            json_trad ();
            printf ( " Archivo xml generado bajo el nombre de \" output.xml \"\n " );
        }
    } más {
        printf ( " Debe pasar como parametro el camino al archivo fuente. \n " );
        salida ( 1 );
    }
    devolver  0 ;
}