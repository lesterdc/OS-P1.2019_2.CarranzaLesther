<h1>Proyecto de SO de Lesther Carranza</h1>
<ul>
    <li><h2>Desing Overview</h2></li>
    <p>El proyecto se encuentra dividido en dos partes, una de ellas
    es el shell y el otro es el comando twc, el cual se explicara a continuacion</p>
        <ol>
        <li><h3>Shell</h3></li>
            <p>Se encuentra dividido en 11 funciones tomando en cuanta la funcion main() la cual es la inicial, estas 11 funciones son las siguientes</p>
            <ol>
                <li><h4>init_shell()</h4></li>
                    <p>En esta funcion muestro un mensaje inicial, imprime el usuario con el cual el usuario esta conectado. Este init solo se mostrara al inicio del shell, por lo que si se desea volver a ver hay que ejecutar de nuevo el shell</p>
                <li><h4>takeInput()</h4></li>
                    <p>Esta funcion es la encargada de mostrar la linea SO'<'201601374>sh% y tambien es la que recibe los datos que se escriban en la shell</p>
                <li><h4>printDir()</h4></li>
                    <p>Aqui imprimo el directorio actual en el cual se encuentra el usuario, para ello use la funcion getcwd que me da el actual directorio de trabajo</p>
                <li><h4>execArgs()</h4></li>
                    <p>Aqui se ejecutaran los comandos que sean del sistema, si no existiera esta funcion mi shell solo podria ejecutar los comandos que yo mismo he hecho y esten disponibles y no los que el SO tengo como ping,ifconfig,etc</p>
                <li><h4>execArgsPiped()</h4></li>
                    <p>En esta funcion el comando pipe "|" es ejecutado, aqui controlo si puedo inicializarlo o no</p>
                <li><h4>openHelp()</h4></li>
                    <p>Es solo una funcion que al escribir en la shell "help" mostrara algo de ayuda sobre mi shell</p>
                <li><h4>ownCmdHandler()</h4></li>
                    <p>Aqui controlo el uso de los comandos que pide en la especificacion del proyecto, estos se pueden ver escribiendo "help" en la consola y son:</p>
                    <ul>
                        <li>exit</li>
                        <li>cd</li>
                        <li>help</li>
                        <li>hello</li>
                        <li>twc</li>
                    </ul>
                    <p>Se encuentran controlados mediante un case</p>
                <li><h4>parsePipe()</h4></li>
                    <p>Aqui nos encargamos de detectar si se esta usando pipe, es decir si se ha escribo el caracter "|"</p>
                <li><h4>parseSpace()</h4></li>
                    <p>Hago el parsin de los comandos que haya usado</p>
                <li><h4>processString()</h4></li>
                    <p>Aqui nos encargamos de realizar todo el pipe</p>
                <li><h4>main()</h4></li>
                    <p>La funcion main es principalmente un loop infinito, aqui principalmente se encuentran las funciones mas importantes que describi previamente para que el shell funcione correctamente y esteticamente agradable</p>
                    <ul>
                        <li>init_shell()</li>
                        <li>printDir()</li>
                        <li>takeInput()</li>
                        <li>processString()</li>
                        <li>execArgs()</li>
                        <li>execArgsPiped()</li>
                    </ul>
            </ol>
        <li><h3>Comando Twc</h3></li>
            <p>El comando Twc es una mejora del comando wc, el comando twc realiza las mismas operaciones pero con la particularidad de que este se realizan mediante hilos creados a partir del numero de procesadores con los que cuente la maquina anfitriona</p>
            <p>En mi implemantacion, lo dividi en tres funciones</p>
            <ol>
                <li><h4>main()</h4></li>
                    <p>La funcion main se maneja principalmente de banderas, las cuales utilizo para controlar la informacion que se mostrara dependiendo de lo que el usuario (el que esta ejecutando el comando) este solicitando.</p>
                    <p>Otro punto que se encuentra dentro de la funcion main, es la lectura del archivo al cual se desea aplicar el comando twc, no lo separe y aplique en otra funcion por que lo vi innecesario, es cierto que por cuestion de mantenimiento futuro en otros casos seria bastante recomendado, pero en este caso la estructura es bastante sencilla como para aplicar</p>
                    <p>Dentro de la lectura del archivo se encuentras los hilos responsables del conteo de los datos que se piden por la entrada estandar</p>
                <li><h4>*thread_function</h4></li>
                    <p>Esta es una funcion para los hilos, al inicio defini una estructura para cada hilo, en esta funcion es en donde controlo esta caracteristica, de esta forma logro que el hilo no solamente lleve el conteo de sus numeros de lineas, sino tambien que lleve el conteo de caracteres y caracteres especiales</p>
                <li><h4>*excess_thread_function</h4></li>
                    <p>Al igual que la funcion anterior, aqui manejo los posibles errores</p>
            </ol>
        </ol>
    <li><h2>Complete Specification</h2></li>
        <p>En el caso de manejo de ambiguedades del shell, se usaron principalmente un grupo de funciones propias como: help, exit, cd, entre otras. Estas funciones son manejadas por el propio shell, mientras que otros comandos como ifconfig el cual no estan desarrolladas en el shell pero se encuentran en el sistema previamente instaladas por el gestor de paquetes correspondiente</p>
        <p>Las lineas de las cuales no tengan comandos especificados, simplemente no se ejecutaran y se mostrara un mensaje que informara que el comando no ha sido encontrado. En caso de existir el comando y no sea propio de la shell, igual se ejecutara normalmente</p>
        <p>Asi mismo con los comandos con doble espacio,tabulaciones y argumentos inexistentes, la estructura de los comandos ya esta establecida por lo que si la sintaxis del comando se encuentra errore, el shell mostrara por la salida estandar informacion sobre la correcta sintaxis del comando</p>
    <li><h2>Know bugs or problems</h2></li>
        <p>En el caso del shell hice dos supuestos, los cuales son que, el usuario no vaya a ingresar en la entrada estandar mas de 100 comandos y mas de 1000 caracteres, en caso de ocurrir estos puntos el shell no soportara la carga y habra un desbordamiento de pila</p>
        <p>En el caso del comando twc, se puede sobrecargar la cantidad de hilos que trabajaran en el conteo logrando crear un limite para el performance de dicho comando</p>
        <p>Como el uso de banderas fue altamente utilizado en el comando twc tambien queda vulnerable a fallos de seguridad, que en cursos previos recomendaban no usarlas en su gran mayoria</p>
</ul>
