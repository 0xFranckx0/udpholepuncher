.PHONY:	build compile run stop punch

SRC=/root/udpholepuncher
IMAGE = builder
TAG = 1-0


build:	
	docker build -t cdev/$(IMAGE):$(TAG) .

compile:
	docker exec -i $(IMAGE) /opt/build.sh

run:
	docker run -d -i --name builder --net=host -v $(SRC):/opt/uhp cdev/builder:1-0 

stop:
	docker stop $(IMAGE) && docker rm $(IMAGE)

punch:
	docker exec -i -t $(IMAGE) /opt/uhp/test -a 192.168.0.10 -p 55555 -m message
