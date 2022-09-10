# Monitoring Carbon Footprint
Measuare and visualize carbon emissions, using IoT Technology .

<img src="Images/cloud.png" width = 290 height=190> <img src ="Images/cloud2.png" width =300 heigh=190>

### What is Climate ?
Climate can be different for different seasons. Although, we can defined climate as the usual weather of a place. It is normal to have different climates. Nevertheless, we have to know what is normal. You're probably thinking, how do we know when the Earth's climate is normal ? To answer this , we have to understand what Climate change is.

### Climate Change.
Climate change is a change in the usual weather found in a place. The changes can be experienced in a number of ways. For instance ,the increase in the climate's temperature or 
sudden decrease in rainfall in a place could be a result of climate change.Infact, what's more important, is how changes in the earth's temeparature affects how we live on it. 

The Earth's temeperature has increased by 1 degree celcius in recent years, and this has caused major problem in our ecosystem.The increase in temperature has caused Earth Ice to melt  causing see levels to rise, the expected time for plant yield is changing ,causing famine. The effects are so much more !
Just imaging if the ocean levels rise into cities or human and inhabited. This is flooding at it's peak ! yup ,very bad !

### What Causes Climate Change ?
Quite alot of things can cause the process of climate change. From volcanos errupting , to changes in the earth's proximity to the sun, even gases being emitted into the atmosphere by vechicles or engines cause Climate Change.

### How Can we Help Sove Climate Change ?
When more and more gases are emitted into the atmosphere, it causes the air to heat up. which means, more Carbon Emissions , more hot air. 
Although, these aren't the only causes to the problem, but this is one way we can reduce the effect of climate change.
Using Carbon Emission Data in one square km, we could rougly estimate and develop useful solution for Carbon emission reduction. 

### This Project !
In this little repo ,we measure how much Carbondioxide is emitted from a common emittant "Automobiles" using CO2 Sensors. The data collected from this project
is used along with Total distance travalled 
and ambient temperature. Thereafter, we can analyze the data to make meaning out of it.







# Getting Started !


First, we need to purchase a few tools for our little project. 
An ESP8266 NodeMCU module, an MQ9 Sensor and an MQ135 Sensor.
Once you have that, we'd need to install the Arduino IDE. 
Use the link below to download the Arduino IDE.




```
https://www.arduino.cc/en/software
```
### Add the Link To "Preferences" in The Arduino IDE !
Open Arduino IDE ----> File ---> Preferences --->Additional Boards Mananger URLs

```
http://arduino.esp8266.com/stable/package_esp8266com_index.json
```
## Prerequisite PHP , MQSQL , C , HTML , CSS
As you Naviagate your way through this repository, you have to be familiar with Languages listed above.

#### SQL
```SQL
CREATE TABLE SensorData (
    id INT(6) UNSIGNED AUTO_INCREMENT PRIMARY KEY,
    sensor1 VARCHAR(30) NOT NULL,
    location VARCHAR(30) NOT NULL,
    value1 VARCHAR(10),
    value2 VARCHAR(10),
    value3 VARCHAR(10),
    value4 VARCHAR(10),
    reading_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
)
```
#### Product Details
See Breadboarding, Schematic , PCB Design and Bill of Materials Below
