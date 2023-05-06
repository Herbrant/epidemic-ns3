FROM ghcr.io/herbrant/ns3-docker:main

RUN mkdir -p /ns3/ns-3.38/scratch/epidemic-ns3
COPY . /ns3/ns-3.38/scratch/epidemic-ns3/

RUN /ns3/ns-3.38/ns3 build

ENTRYPOINT [ "/ns3/ns-3.38/scratch/epidemic-ns3/entrypoint.sh" ]
