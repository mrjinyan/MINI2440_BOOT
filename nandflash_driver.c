¡/* 
    you should know about the upper interface, then you can know what to do.
 	1: platform_driver: probe, remove, shutdown, suspend, resume, driver, id_table
	2: functionility of each function?
	3: probe, the entry function, run after the matching of device. 
		detect if there is alive device? so how to detect it? how to know if there is a physical device waiting to be drived?
		then? you know nothing.
		OK, you already know about some thing about nandflash controller.
 */



	//enable clk and do io address remap.
	//1: clk?
	struct clk* nand_clk = clk_get(&pdev->dev,"nand");
	clk_enable(nand_clk);
	//2: io? you need to know the io address to vm, dynamic. how to get the resource of a platform_device?
	struct resource *res = pdev->resource;
	int size = res->end - res->start + 1;
	//register physical address
	struct resource *regis_phy = request_mem_region(res->start,size,pdev->name);
	//map the physical address to visual address.
	void *__iomem reg_base = ioremap(res->start, size);
	//3: begin to initialize the nandflash controller.
	//use nandflash-related bsp offered by Linux directly?
	//3.1: configure the timing parameters.
	//3.2: NFCONF,NFCONT,NFSTAT
	//4: intialize nand_chip member. another stage, after this basic function has already been prepared.
	//you should know about nand_chip.
	//5:

