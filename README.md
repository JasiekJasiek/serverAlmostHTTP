# Server 
* [General info](#general-info)
* [Setup](#setup)
* [How to use?](#how-to-use)
  
## General info
<details>
<summary>Click here to see general information about <b>Project</b>!</summary>

This code works similarly to HTTP servers, but has a changed protocol for only sending files in both directions, as well as deleting files from the server remotely. This server uses such technology that allows data to be sent not only on the local network. Using this code can save you money that you would normally spend on a cloud subscription.  

</details>

## Setup

<details>
<summary>Click here to see how to setup!</summary>

* on server computer run `g++ -std=c++17 -Wall -o server/server server/server.cpp && ./server/server`
* on client computer run `g++ -std=c++17 -Wall -o client/client client/client.cpp && ./client/client`
* in `clinet/client.cpp` you have to put our server IP addres in line 19 in HTTPClinet instance
  
</details>

## How to use?

<details>
<summary>Click here to see how to use?</summary>

### Comunication protocol uses 3 main commands:

* #### GET
  Get is used to download a file from the server, e.g.: <br>
  `GET story.txt` will download `story.txt` file from the server
* #### PUT
  PUT is used to upload a file to the server, e.g.: <br>
  `PUT story.txt` will upload `story.txt` file to the server
* #### DELETE
  DELETE is used to remotely delete files that already exist on the server, e.g.: <br>
  `DELETE story.txt` will delete `story.txt` file from the server
  
  
</details>
