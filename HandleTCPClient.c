//
//  HandleTCPClient.c
//  Sockets
//
//  Created by Felix Xiao on 9/23/14.
//  Copyright (c) 2014 Felix Xiao. All rights reserved.
//

#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for recv() and send() */
#include <unistd.h>     /* for close() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>

#define RCVBUFSIZE 32   /* Size of receive buffer */

void DieWithError(char *errorMessage);  /* Error handling function */

void HandleTCPClient(int clntSocket)
{
    char echoBuffer[RCVBUFSIZE];        /* Buffer for echo string */
    int recvMsgSize;                    /* Size of received message */
    
    /* Receive message from client */
    if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
        DieWithError("recv() failed");
    
    /* Send received string and receive again until end of transmission */
    while (recvMsgSize > 0)      /* zero indicates end of transmission */
    {
        //split the inputs so that it knows what to add
        //set echoBuffer as the answer
        //http://stackoverflow.com/questions/11198604/c-split-string-into-an-array-of-strings
        //I used this resource
        int i;
        char *p;
        char *array[2];
        int sum = 0;
        i = 0;
        p = strtok (echoBuffer,","); //splits the input by the comma
        while (p != NULL) //this while loop inputs everything into an array
        {
            array[i++] = p;
            p = strtok (NULL, ",");
        }
        for (i=0;i<2; ++i)
            sum = sum + atoi(array[i]);
        
        snprintf(echoBuffer, sizeof(echoBuffer), "%i",sum); //change it to a char* to send back to echoBuffer via next lines
        
        /* Echo message back to client */
        if (send(clntSocket, echoBuffer, recvMsgSize, 0) != recvMsgSize)
            DieWithError("send() failed");
        
        /* See if there is more data to receive */
        if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
            DieWithError("recv() failed");
    }
    
    close(clntSocket);    /* Close client socket */
}
