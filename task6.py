import requests

def get_elevation(api_key, lat, lon):
    base_url = "https://maps.gomaps.pro/maps/api/elevation/json"
    params = {
        "locations": f"{lat},{lon}",
        "key": api_key
    }

    response = requests.get(base_url, params=params)
    
    if response.status_code == 200:
        data = response.json()
        if data["status"] == "OK":
            elevation = data["results"][0]["elevation"]
            return elevation
        else:
            print(f"Request failed: {data['status']}")
            return None
    else:
        print("Failed to make the request. Status code:", response.status_code)
        return None

def get_distance_duration(api_key, start, end):
    base_url = "https://maps.gomaps.pro/maps/api/distancematrix/json"
    params = {
        "origins": start,
        "destinations": end,
        "key": api_key
    }

    response = requests.get(base_url, params=params)

    if response.status_code == 200:
        data = response.json()
        if data["status"] == "OK":
            distance = data["rows"][0]["elements"][0]["distance"]["text"]
            duration = data["rows"][0]["elements"][0]["duration"]["text"]
            return distance, duration
        else:
            print(f"Request failed: {data['status']}")
            return None, None
    else:
        print("Failed to make the request. Status code:", response.status_code)
        return None, None

def get_directions(api_key, origin, destination):
    base_url = "https://maps.gomaps.pro/maps/api/directions/json"
    
    params = {
        "origin": origin,
        "destination": destination,
        "key": api_key
    }
    
    response = requests.get(base_url, params=params)
    
    if response.status_code == 200:
        data = response.json()

        if data["status"] == "OK":
            route = data["routes"][0]
            legs = route["legs"][0]
            distance = legs["distance"]["text"]
            duration = legs["duration"]["text"]
            steps = legs["steps"]
            directions = []
            for step in steps:
                html_instructions = step["html_instructions"]
                clean_instructions = html_instructions.replace('<b>', '').replace('</b>', '').replace('<div style="font-size:0.9em">', ' ').replace('</div>', '')
                directions.append(clean_instructions)

            return distance, duration, directions
        else:
            print(f"Request failed: {data['status']}")
            return None, None, None
    else:
        print("Failed to make the request. Status code:", response.status_code)
        return None, None, None

def get_latitude_longitude(api_key, address):
    url = 'https://maps.gomaps.pro/maps/api/geocode/json'
    params = {
        "address": address,
        "key": api_key
    }

    response = requests.get(url, params=params)

    if response.status_code == 200:
        data = response.json()
        if data["status"] == "OK":
            location = data["results"][0]["geometry"]["location"]
            lat = location["lat"]
            lng = location["lng"]
            return lat, lng
        else:
            print(f"Error: {data['status']}")
            return None, None
    else:
        print("Failed to make the request. Status code:", response.status_code)
        return None, None

# Example usage
api_key = "AlzaSytZZg3GVg6YXT4Wi5h0DWn48dJr6b6mUmX"  # Replace with your GoMap API key

# Get latitude and longitude
address = '43F2+7JR, S Ambazari Rd, Ambazari, Nagpur, Maharashtra 440010'
lati, longi = get_latitude_longitude(api_key, address)
print(f"Latitude: {lati}, Longitude: {longi}")

# Get elevation
if lati is not None and longi is not None:
    elevation = get_elevation(api_key, lati, longi)
    if elevation is not None:
        print(f"Elevation at ({lati}, {longi}): {elevation} meters")

# Get distance and duration
start = "Jaripatka, Nagpur, Maharashtra 440024"
end = "43F2+7JR, S Ambazari Rd, Ambazari, Nagpur, Maharashtra 440014"
distance, duration = get_distance_duration(api_key, start, end)

if distance and duration:
    print(f"Driving Distance: {distance}")
    print(f"Driving Duration: {duration}")

# Get directions
distance, duration, directions = get_directions(api_key, start, end)

if distance and duration:
    print(f"Total Distance: {distance}")
    print(f"Total Duration: {duration}")
    print("Directions:")
    for step in directions:
        print(step)
