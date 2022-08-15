import gspread
gc = gspread.service_account("./DHT22-pi3-credentials.json")
sh = gc.open("dht22rpi3")
print(sh.sheet1.get("A1"))

