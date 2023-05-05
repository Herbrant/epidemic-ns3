FROM ghcr.io/herbrant/ns3-docker:main

RUN mkdir -p /ns3/ns-3.38/scratch/epidemic-ns3
COPY . /ns3/ns-3.38/scratch/epidemic-ns3/

ENTRYPOINT [ "/ns3/ns-3.38/ns3", "run", "epidemic-benchmark" ]
