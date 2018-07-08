.PHONY:	build compile run stop punch

SRC=/root/puncher
IMAGE = builder
TAG = 1-6


build:	
	docker build -t cdev/$(IMAGE):$(TAG) .

compile:
	docker exec -i $(IMAGE) /opt/build.sh

run:
	docker run -d -i --name $(IMAGE) --net=host -v $(SRC):/opt/uhp cdev/$(IMAGE):$(TAG)

stop:
	docker stop $(IMAGE) && docker rm $(IMAGE)

punch:
	docker exec -i -t $(IMAGE) /usr/local/bin/proto_test -a 192.168.0.10 -p 55555 -m message
