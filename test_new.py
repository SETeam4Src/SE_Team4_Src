import serial
import MySQLdb
from time import localtime, strftime
import time as t

time = strftime("%Y%m%d %H%M%S", localtime())
S = serial.Serial('COM6',9600)

before_status = ""
after_status =""


before_status = S.readline()
first_value = 1

getInform = ""

i = 0;
j = 0;

while True:

 db = MySQLdb.connect(host='localhost', user='root', passwd = 'asdf',db='testdb')
  
 if first_value == 1:
    
       with db:
        print "first value : %s %s " % (time,before_status[:-2])   
        cur = db.cursor()
        cur.execute("INSERT INTO message_inform(time,getInform) VALUES (%s, %s)" , (time,before_status))
        db.commit()
       
       if "TV" in before_status:
	     
          with db:
           cur = db.cursor()
           cur.execute("INSERT INTO monitoring(time,getTV) VALUES (%s, %s)" , (time,before_status))
           db.commit()
		 
        
       first_value = first_value + 1
       after_status = before_status
  
 if before_status != after_status: 

     with db:
        print "change value : %s %s " % (time,before_status[:-2]) 
        cur = db.cursor()
        cur.execute("INSERT INTO message_inform(time,getInform) VALUES (%s, %s)" , (time,before_status))
        db.commit()
	 
     if "TV" in before_status:
	     
          with db:
           cur = db.cursor()
           cur.execute("INSERT INTO monitoring(time,getTV) VALUES (%s, %s)" , (time,before_status))
           db.commit()
		 	 
			 
     after_status = before_status
     
   

 before_status = S.readline()
 time = strftime("%Y%m%d %H%M%S", localtime())