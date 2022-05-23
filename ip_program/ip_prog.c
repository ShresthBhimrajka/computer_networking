#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void bin_to_dec(int bin[], int dec[])
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

void dec_to_bin(int bin[], int dec[])
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

void find_ip(int bin[], int mask, int first_addr_bin[], int last_addr_bin[])
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
    char ip_cidr[18];
    printf("Enter the IP in CIDR: ");
    scanf("%s", &ip_cidr);

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

    while(i < strlen(ip_cidr))
    {
        mask = mask*10 + (ip_cidr[i] - '0');
        i++;
    }

    printf("Given IP: %d", dec[0]);
    for(i = 1 ; i < 4 ; i++)
        printf(":%d", dec[i]);
    printf("\nMask: %d\n", mask);

    for(i = 0 ; i < 32 ; i++)
    {
        if(i < mask)
            subnet_bin[i] = 1;
        else
            subnet_bin[i] = 0;
    }

    bin_to_dec(subnet_bin, subnet_dec);

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

    dec_to_bin(bin, dec);

    printf("\nIP in binary: ");
    for(i = 0 ; i < 32 ; i++)
    {
        if(i == 8 || i == 16 || i == 24)
            printf(":");
        printf("%d", bin[i]);
    }

    find_ip(bin, mask, first_addr_bin, last_addr_bin);

    bin_to_dec(first_addr_bin, first_addr_dec);

    bin_to_dec(last_addr_bin, last_addr_dec);

    printf("\nFirst address in binary: ");
    for(i = 0 ; i < 32 ; i++)
    {
        if(i == 8 || i == 16 || i == 24)
            printf(":");
        printf("%d", first_addr_bin[i]);
    }

    printf("\nLast address in binary: ");
    for(i = 0 ; i < 32 ; i++)
    {
        if(i == 8 || i == 16 || i == 24)
            printf(":");
        printf("%d", last_addr_bin[i]);
    }

    printf("\nFirst address: %d", first_addr_dec[0]);
    for(i = 1 ; i < 4 ; i++)
        printf(":%d", first_addr_dec[i]);

    printf("\nLast address: %d", last_addr_dec[0]);
    for(i = 1 ; i < 4 ; i++)
        printf(":%d", last_addr_dec[i]);
}
