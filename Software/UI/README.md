<h2>Description of UI</h2>
<p>This path contains a project with a desktop Windows app for communication via UART from a computer to an electrospinning device based on an Arduino Mega or ATmega2560 microcontroller.</p>
<h3>Steps for using the device and protocol</h3>
<ul>
    <li>The app has a dropdown menu for viewing and selecting available COM ports.</li>
    <li>It also has a button to connect to the device and informs us if the connection was successful or if the connection was lost.</li>
    <li>There is a window where we can see the voltage, one for motor speed, and the last one for time (actual/necessary for the process), and all the parameters can also be adjusted.</li>
    <li>The protocol sends messages in the format: voltage, speed, time. When the device is working, we have two values for time: one is the total time needed for the experiment and the other is the actual time in the process.</li>
    <li>There are also two buttons for starting and stopping the process.</li>
    <li>The protocol looks like this: <i>9000,50,60,3</i> If the process is not running, then the last value is -1.</li>
</ul>
