<h1>Electrospinning Device based on Arduino Mega</h1>

<p>This repository contains the source code, hardware schematics, and documentation for a device designed to facilitate the electrospinning process using the Arduino Mega microcontroller. The device allows control and monitoring of various parameters involved in electrospinning, enabling researchers and enthusiasts to experiment with this technique.</p>

<h2>Contents</h2>

<ul>
  <li><a href="#features">Features</a></li>
  <li><a href="#hardware-setup">Hardware Setup</a></li>
  <li><a href="#usage">Usage</a></li>
  <li><a href="#contributing">Contributing</a></li>
  <li><a href="#license">License</a></li>
</ul>

<h2>Features</h2>

<p>The device provides the following features:</p>
<ul>
  <li>Control and monitoring of various parameters involved in the electrospinning process.</li>
  <li>Integration with Arduino Mega microcontroller for easy customization and expansion.</li>
  <li>High voltage source consisting of ZVS driver, flyback transformer, capacitors, and voltage divider for measuring the output voltage.</li>
  <li>ILI4931 screen with touch for user interface.</li>
  <li>2 motors for controlling the electrospinning process.</li>
  <li>L293D driver for regulating the amount that passes through the syringe.</li>
</ul>

<h2>Hardware Setup</h2>

<p>The hardware setup consists of the following components:</p>
<ul>
  <li>ZVS driver</li>
  <li>Flyback transformer</li>
  <li>Capacitors</li>
  <li>Voltage divider</li>
  <li>Arduino Mega microcontroller</li>
  <li>ILI4931 screen with touch</li>
  <li>2 motors</li>
  <li>L293D driver</li>
</ul>

<h3>High voltage schematic</h3>
<img src="Images/HVS.jpg" alt="High voltage source" width="300">

<h2>Usage</h2>

<p>To use the electrospinning device:</p>
<ol>
  <li>Connect the high voltage source components according to the provided schematics.</li>
  <li>Connect the Arduino Mega to the components and upload the provided source code.</li>
  <li>Use the ILI4931 screen with touch to control and monitor the electrospinning process.</li>
  <li>Adjust the settings as needed and start the electrospinning process.</li>
  <li>Monitor the output and make adjustments as necessary.</li>
</ol>

<h2>Contributing</h2>

<p>Contributions to this project are welcome. Please fork the repository, make your changes, and submit a pull request.</p>

<h2>License</h2>

<p>This project is licensed under the <a href="LICENSE">MIT License</a>.</p>
