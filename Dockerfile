#OS
FROM archlinux:latest

#Environment variables
ENV TERM=xterm-256color
ENV LANG=C.UTF-8

#System tools
RUN pacman -Syu --noconfirm \
    base-devel \
    gcc \
    git \
    cmake \
    ninja \
    python \
    curl \
    && pacman -Scc --noconfirm

# Downloading and using micromamba
ENV MAMBA_ROOT_PREFIX=/opt/micromamba
ENV PATH=/opt/micromamba/bin:$PATH

RUN pacman -Syu --noconfirm ca-certificates curl \
    && update-ca-trust

# Libmamba stability
ENV MAMBA_NO_IPV6=1
ENV MAMBA_NUM_THREADS=1

# Micromamba install 
RUN curl -L https://micro.mamba.pm/api/micromamba/linux-64/latest \
    | tar -xvj bin/micromamba \
    && mv bin/micromamba /usr/local/bin/micromamba

# Create environment 
RUN micromamba create -y -n class-env \
    -c conda-forge \
    xeus-cling \
    jupyterlab \
    notebook \
    && micromamba clean --all --yes

#Activate environment
SHELL ["/bin/bash", "-c"]

# Initialize micromamba shell support
RUN micromamba shell init --shell bash --root-prefix=/opt/micromamba

# Auto-activate the environment for every shell
RUN echo "micromamba activate class-env" >> /root/.bashrc

#Workspace
WORKDIR /workspace
EXPOSE 8888
CMD ["bash", "-l", "-c", "tail -f /dev/null"]
