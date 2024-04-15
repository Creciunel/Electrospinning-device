<h2>Description of UI</h2>
<p>This path contains a project with a desktop Windows app for communication via UART from a computer to an electrospinning device based on an Arduino Mega or ATmega2560 microcontroller.</p>
<h3>Steps for using the device and protocol</h3>
<ul>
    <li>
        The app has a dropdown menu for viewing and selecting available COM ports.
    </li>
    <li>
        It also has a button to connect to the device and informs us if the connection was successful or if the connection was lost.
    </li>
    <li>
        There is a window where we can see the voltage, one for motor speed, and the last one for time (actual/necessary for the process), and all the parameters can also be adjusted.
    </li>
    <li>
        The protocol sends messages in the format:<i><b>status, sart/stop, voltage, speed, time.</b></i> When the device is working, we have two values for time: one is the total time needed for the experiment and the other is the actual time in the process.
    </li>
    <li>There are also two buttons for starting and stopping the process.</li>
    <li>
        The protocol looks like this: <i>1,1,9000,50,60,3</i>. If the process is not running, then the last value of status state is false (0).
    </li>
    <li>
        If there is a problem, the message will start with <b>0</b>, which means errors, and that will be an error message such as: <i>0, TFT display error</i>.
    </li>
</ul>
<h3>Comunication</h3>
    <p>Additionally, the application also sends messages to the execution, such as the processing time or speed.</p>
    <p>The format is <i>key-value</i> with s1 or m10.</p>
    <table>
        <tr>
            <th>Key</th>
            <th>Value</th>
        </tr>
        <tr>
            <th>s</th>
            <th>1 or 0</th>
        </tr>
        <tr>
            <th>m</th>
            <th>0 to 100 or more </th>
        </tr>
        <tr>
            <th>n</th>
            <th>0 to 100 or more </th>
        </tr>
        <tr>
            <th>t</th>
            <th>0 to 100 or more </th>
        </tr>
    </table>
<ul>
    <li>s - comes from start stop</li>
    <li>m - comes from motor speed</li>
    <li>n - comes from motor numbers of revolution</li>
    <li>t - comes from time</li>
</ol>
