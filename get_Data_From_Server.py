#####################################
    #Author: Hariharan Raveenthiran
#####################################

#This file gets the command that was posted in cloud, converts it to audio so that user will be notified.

from urllib.request import urlopen
import json
import time
from gtts import gTTS
import os

READ_API_KEY='' #Read api key of the cloud that you are using (I am using thingspeak)
CHANNEL_ID= ''  #Channel ID of the clould channel that your are using


while True:
    TS = urlopen("http://api.thingspeak.com/channels/%s/feeds/last.json?api_key=%s" \
                       % (CHANNEL_ID,READ_API_KEY))

    response = TS.read()
    data=json.loads(response)
    b = data['field1']
    print (b) 
    mytext =b
    language = 'en'
    myobj = gTTS(text=mytext, lang=language, slow=False)
    myobj.save("Command.mp3")
    os.system("mpg321 Command.mp3")
    time.sleep(5)   
    TS.close()