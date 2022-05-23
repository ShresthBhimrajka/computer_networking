#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void bin_to_dec(int bin[], int dec[]) // Function to convert binary array to decimal array
{
    int start_in = 0;
    int end_in = 7;
    int i = 0;
    int j = 0;
    for(i = 0 ; i < 4 ; i++)
    {
        int sum = 0;
        for(j = start_in ; j <= end_in ; j++)
        {
            int p = 7 - (j - start_in);
            sum = sum + bin[j]*pow(2, p);
        }
        start_in += 8;
        end_in += 8;
        dec[i] = sum;
    }
}

void dec_to_bin(int bin[], int dec[]) // Function to convert decimal array to binary array
{
    int start_in = 0;
    int end_in = 7;
    int i = 0;
    int j = 0;
    for(i = 0 ; i < 4 ; i++)
    {
        int x = dec[i];
        for(j = end_in ; j >= start_in ; j--)
        {
            bin[j] = x % 2;
            x /= 2;
        }
        start_in += 8;
        end_in += 8;
    }
}

void find_ip(int bin[], int mask, int first_addr_bin[], int last_addr_bin[]) // Function to find the first and last address in binary
{
    int i = 0;
    for(i = 0 ; i < 32 ; i++)
    {
        first_addr_bin[i] = bin[i];
        last_addr_bin[i] = bin[i];
        if(i >= mask)
        {
            first_addr_bin[i] = 0;
            last_addr_bin[i] = 1;
        }
    }
}

void main()
{
    // Read the IP in CIDR
    char ip_cidr[18];
    printf("Enter the IP in CIDR: ");
    scanf("%s", &ip_cidr);

    // Array declarations
    int bin[32];
    int dec[4];
    int subnet_bin[32];
    int subnet_dec[4];
    int first_addr_bin[32];
    int last_addr_bin[32];
    int first_addr_dec[4];
    int last_addr_dec[4];
    int mask = 0;
    int i = 0;
    int k = 0;

    // Assigning default values
    for(i = 0 ; i < 32 ; i++)
    {
        first_addr_bin[i] = 0;
        last_addr_bin[i] = 0;
        bin[i] = 0;
    }
    for(i = 0 ; i < 4 ; i++)
    {
        first_addr_dec[i] = 0;
        last_addr_dec[i] = 0;
        subnet_dec[i] = 0;
        dec[i] = 0;
    }

    // Converting the IP from string to decimal
    i = 0;
    for(k = 0 ; k < 4 ; k++)
    {
        int x = 0;
        x = x*10 + (ip_cidr[i] - '0');
        i += 1;
        while(ip_cidr[i] != '.' && ip_cidr[i] != '/' && i < strlen(ip_cidr))
        {
            x = x*10 + (ip_cidr[i] - '0');
            i++;
        }
        i += 1;
        dec[k] = x;
    }

    // Converting the mask from string to decimal
    while(i < strlen(ip_cidr))
    {
        mask = mask*10 + (ip_cidr[i] - '0');
        i++;
    }

    // Print the IP and mask
    printf("Given IP: %d", dec[0]);
    for(i = 1 ; i < 4 ; i++)
        printf(":%d", dec[i]);
    printf("\nMask: %d\n", mask);

    // Generate the subnet in binary
    for(i = 0 ; i < 32 ; i++)
    {
        if(i < mask)
            subnet_bin[i] = 1;
        else
            subnet_bin[i] = 0;
    }

    // Convert the subnet from binary to decimal
    bin_to_dec(subnet_bin, subnet_dec);

    // Print the subnet
    printf("Subnet in binary: ");
    for(i = 0 ; i < 32 ; i++)
    {
        if(i == 8 || i == 16 || i == 24)
            printf(":");
        printf("%d", subnet_bin[i]);
    }
    printf("\nSubnet in decimal: %d", subnet_dec[0]);
    for(i = 1 ; i < 4 ; i++)
        printf(":%d", subnet_dec[i]);

    // Convert the IP from decimal to binary
    dec_to_bin(bin, dec);

    // Print the IP
    printf("\nIP in binary: ");
    for(i = 0 ; i < 32 ; i++)
    {
        if(i == 8 || i == 16 || i == 24)
            printf(":");
        printf("%d", bin[i]);
    }

    // Find the first and last address in binary
    find_ip(bin, mask, first_addr_bin, last_addr_bin);

    // Convert the first address from binary to decimal
    bin_to_dec(first_addr_bin, first_addr_dec);

    // Convert the last address from binary to decimal
    bin_to_dec(last_addr_bin, last_addr_dec);

    // Print the first address in binary
    printf("\nFirst address in binary: ");
    for(i = 0 ; i < 32 ; i++)
    {
        if(i == 8 || i == 16 || i == 24)
            printf(":");
        printf("%d", first_addr_bin[i]);
    }

    //Print the last address in binary
    printf("\nLast address in binary: ");
    for(i = 0 ; i < 32 ; i++)
    {
        if(i == 8 || i == 16 || i == 24)
            printf(":");
        printf("%d", last_addr_bin[i]);
    }

    // Print the first address in decimal
    printf("\nFirst address: %d", first_addr_dec[0]);
    for(i = 1 ; i < 4 ; i++)
        printf(":%d", first_addr_dec[i]);

    // Print the last address in decimal
    printf("\nLast address: %d", last_addr_dec[0]);
    for(i = 1 ; i < 4 ; i++)
        printf(":%d", last_addr_dec[i]);
}
