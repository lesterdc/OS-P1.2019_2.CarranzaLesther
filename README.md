<h1>Proyecto de SO de Lesther Carranza</h1>
<ul>
    <li><h2>Desing Overview</h2></li>
    <p>El proyecto se encuentra dividido en dos partes, una de ellas
    es el shell y el otro es el comando twc, el cual se explicara a continuacion</p>
        <ol>
        <li>Shell</li>
            <p>Se encuentra dividido en 11 funciones tomando en cuanta la funcion main() la cual es la inicial, estas 11 funciones son las siguientes</p>
            <ol>
                <li>init_shell()</li>
                    <p>En esta funcion muestro un mensaje inicial, imprime el usuario con el cual el usuario esta conectado. Este init solo se mostrara al inicio del shell, por lo que si se desea volver a ver hay que ejecutar de nuevo el shell</p>
                <li>takeInput()</li>
                    <p>Esta funcion es la encargada de mostrar la linea SO'<'201601374>sh% y tambien es la que recibe los datos que se escriban en la shell</p>
                <li>printDir()</li>
                    <p>Aqui imprimo el directorio actual en el cual se encuentra el usuario, para ello use la funcion getcwd que me da el actual directorio de trabajo</p>
                <li>execArgs()</li>
                    <p>Aqui se ejecutaran los comandos que sean del sistema, si no existiera esta funcion mi shell solo podria ejecutar los comandos que yo mismo he hecho y esten disponibles y no los que el SO tengo como ping,ifconfig,etc</p>
                <li>execArgsPiped()</li>
                    <p>En esta funcion el comando pipe "|" es ejecutado, aqui controlo si puedo inicializarlo o no</p>
                <li>openHelp()</li>
                    <p>Es solo una funcion que al escribir en la shell "help" mostrara algo de ayuda sobre mi shell</p>
                <li>ownCmdHandler()</li>
                    <p>Aqui controlo el uso de los comandos que pide en la especificacion del proyecto, estos se pueden ver escribiendo "help" en la consola y son:</p>
                    <ul>
                        <li>exit</li>
                        <li>cd</li>
                        <li>help</li>
                        <li>hello</li>
                        <li>twc</li>
                    </ul>
                    <p>Se encuentran controlados mediante un case</p>
                <li>parsePipe()</li>
                    <p>Aqui nos encargamos de detectar si se esta usando pipe, es decir si se ha escribo el caracter "|"</p>
                <li>parseSpace()</li>
                    <p>Hago el parsin de los comandos que haya usado</p>
                <li>processString()</li>
                    <p>Aqui nos encargamos de realizar todo el pipe</p>
                <li>main()</li>
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
        <li>Comando Twc</li>
        </ol>
    <li><h2>Complete Specification</h2></li>
    <li><h2>Know bugs or problems</h2></li>
</ul>
